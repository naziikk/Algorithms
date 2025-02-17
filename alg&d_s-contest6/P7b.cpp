#include <iostream>
#include <vector>

class TwoSATSolver {
    int n_;
    std::vector<std::vector<int>> graph_;
    std::vector<std::vector<int>> transposed_graph_;
    std::vector<int> visited;
    std::vector<int> order;
    std::vector<int> components_distribution;

public:
    std::vector<int> distribution;

    TwoSATSolver(int n) : n_(n) {
        graph_.resize(2 * n);
        transposed_graph_.resize(2 * n);
        distribution.assign(n, -1);
        visited.assign(n * 2, -1);
        components_distribution.assign(n * 2, -1);
    }

    void AddDisjunction(int i1, int e1, int i2, int e2) {
        i1 = 2 * i1 ^ e1;
        i2 = 2 * i2 ^ e2;
        int neg_i1 = i1 ^ 1;
        int neg_i2 = i2 ^ 1;
        graph_[neg_i1].push_back(i2);
        graph_[neg_i2].push_back(i1);
        transposed_graph_[i2].push_back(neg_i1);
        transposed_graph_[i1].push_back(neg_i2);
    }

    void dfs1(int vertex) {
        visited[vertex] = 1;
        for (const auto& neighbour : graph_[vertex]) {
            if (visited[neighbour] == -1) {
                dfs1(neighbour);
            }
        }
        order.push_back(vertex);
    }

    void dfs2(int vertex, int component) {
        components_distribution[vertex] = component;
        for (const auto& neighbour : transposed_graph_[vertex]) {
            if (components_distribution[neighbour] == -1) {
                dfs2(neighbour, component);
            }
        }
    }

    void solveTwoSAT() {
        order.clear();
        visited.assign(n_ * 2, -1);
        for (int i = 0; i < n_ * 2; i++) {
            if (visited[i] == -1) {
                dfs1(i);
            }
        }

        int component = 0;
        components_distribution.assign(n_ * 2, -1);
        while (!order.empty()) {
            int vertex = order.back();
            order.pop_back();
            if (components_distribution[vertex] == -1) {
                dfs2(vertex, component++);
            }
        }

        distribution.assign(n_, -1);
        for (int i = 0;  i < 2 * n_; i += 2) {
            if (components_distribution[i] == components_distribution[i + 1]) {
                return;
            }
            distribution[i / 2] = (components_distribution[i] > components_distribution[i + 1]) ? 1 : 0;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    while (std::cin >> n >> m) {
        TwoSATSolver solver(n);
        int i1, e1, i2, e2;
        for (int i = 0; i < m; i++) {
            std::cin >> i1 >> e1 >> i2 >> e2;
            solver.AddDisjunction(i1, e1, i2, e2);
        }
        solver.solveTwoSAT();
        for (int i = 0; i < n; i++) {
            std::cout << !solver.distribution[i];
        }
        std::cout << '\n';
    }
    return 0;
}