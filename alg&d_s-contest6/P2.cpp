#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

class DSU {
    std::vector<int> parent;
    std::vector<int> rank;

public:
    explicit DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int Find(int vertex) {
        if (vertex == parent[vertex]) {
            return vertex;
        }
        return parent[vertex] = Find(parent[vertex]);
    }

    void Unite(int vertex_a, int vertex_b) {
        int root_a = Find(vertex_a);
        int root_b = Find(vertex_b);
        if (root_a == root_b) {
            return;
        }
        if (rank[root_a] < rank[root_b]) {
            std::swap(root_a, root_b);
        }
        parent[root_b] = root_a;
        if (rank[root_a] == rank[root_b]) {
            rank[root_a]++;
        }
    }
};

struct Edge {
    int from;
    int to;
    int weight;
    int index;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

std::pair<std::unordered_set<int>, int> buildMST(int n, std::vector<Edge>& edge_list, int skip_index = -1, int add = -1) {
    DSU dsu(n);
    int total_weight = 0;
    int edges_used = 0;

    if (add != -1) {
        const auto& edge = edge_list[add];
        dsu.Unite(edge.from, edge.to);
        total_weight += edge.weight;
        edges_used++;
    }
    std::unordered_set<int> st;
    for (int i = 0; i < edge_list.size(); i++) {
        if (i == skip_index) continue;
        const auto& edge = edge_list[i];
        if (dsu.Find(edge.from) != dsu.Find(edge.to)) {
            dsu.Unite(edge.from, edge.to);
            total_weight += edge.weight;
            st.insert(edge.index);
            edges_used++;
        }
    }
    return {st, edges_used == n - 1 ? total_weight : INT_MAX};
}

std::pair<int, int> findTwoMinimumMSTs(int n, std::vector<Edge> &edges) {
    std::sort(edges.begin(), edges.end());
    auto [st, minMST] = buildMST(n, edges);
    int secondMST = std::numeric_limits<int>::max();

    for (int i = 0; i < edges.size(); i++) {
        auto [temp_st, weight] = buildMST(n, edges, edges[i].index);
        if (weight >= minMST && temp_st != st) {
            secondMST = std::min(secondMST, weight);
        }
    }

    return {minMST, secondMST};
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges.push_back({u - 1, v - 1, w, i});
    }

    auto [first_min, second_min] = findTwoMinimumMSTs(n, edges);
    std::cout << first_min << ' ' << second_min;
    return 0;
}
