#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<long long>> dp;
std::vector<int> answer_vertexes;

class FindAnswer {
public:
    static void func(int vertex, int prev, bool marked, std::vector<std::vector<int>>& tree) {
        if (!marked) {
            for (const auto& neighbour : tree[vertex]) {
                if (neighbour != prev) {
                    func(neighbour, vertex, true, tree);
                }
            }
        } else {
            answer_vertexes.push_back(vertex);
            for (const auto& neighbour : tree[vertex]) {
                if (neighbour != prev) {
                    if (dp[neighbour][0] > dp[neighbour][1]) {
                        func(neighbour, vertex, true, tree);
                    } else {
                        func(neighbour, vertex, false, tree);
                    }
                }
            }
        }
    }

    static void dfs(int root, int prev, std::vector<std::vector<int>>& tree, std::vector<int>& cost_per_vertex) {
        dp[root][1] = cost_per_vertex[root];
        dp[root][0] = 0;
        for (const auto& neighbour : tree[root]) {
            if (neighbour != prev) {
                dfs(neighbour, root, tree, cost_per_vertex);
                dp[root][0] += dp[neighbour][1];
                dp[root][1] += std::min(dp[neighbour][0], dp[neighbour][1]);
            }
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> tree(n + 1);
    dp.assign(n + 1, std::vector<long long>(2));
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    std::vector<int> cost_per_vertex(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> cost_per_vertex[i];
    }
    if (n == 1) {
        std::cout << cost_per_vertex[1] << ' ' << 1 << '\n' << 1;
        return 0;
    }
    FindAnswer::dfs(1, 0, tree, cost_per_vertex);
    long long answer = std::min(dp[1][0], dp[1][1]);
    if (dp[1][0] > dp[1][1]) {
        FindAnswer::func(1, 0, true, tree);
    } else {
        FindAnswer::func(1, 0, false, tree);
    }
    std::cout << answer << " " << answer_vertexes.size() << '\n';
    for (const auto& vertex : answer_vertexes) {
        std::cout << vertex << " ";
    }
    return 0;
}