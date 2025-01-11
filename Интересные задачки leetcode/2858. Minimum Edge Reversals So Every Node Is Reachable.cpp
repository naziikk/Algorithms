#include <iostream>
#include <vector>
#include <set>

class Solution {
    std::vector<int> dp;
    std::vector<std::vector<std::pair<int, int>>> graph;
    std::vector<int> ans;

    void findValuesDP(int vertex, int prev) {
        for (const auto& [neighbour, is_reversed] : graph[vertex]) {
            if (neighbour != prev) {
                findValuesDP(neighbour, vertex);
                dp[vertex] += dp[neighbour] + is_reversed;
            }
        }
    }

    void dfs(int vertex, int prev) {
        for (const auto& [neighbour, is_reversed] : graph[vertex]) {
            if (neighbour != prev) {
                ans[neighbour] += ans[vertex] + (!is_reversed ? 1 : -1);
                dfs(neighbour, vertex);
            }
        }
    }
public:
    std::vector<int> minEdgeReversals(int n, std::vector<std::vector<int>>& edges) {
        dp.resize(n, 0);
        ans.resize(n, 0);
        graph.resize(n);
        for (const auto& edge : edges) {
            int from = edge[0];
            int to = edge[1];
            graph[from].emplace_back(to, 0);
            graph[to].emplace_back(from, 1);
        }
        dp[0] = 0;
        findValuesDP(0, -1);
        ans[0] = dp[0];
        dfs(0, -1);
        return ans;
    }
};