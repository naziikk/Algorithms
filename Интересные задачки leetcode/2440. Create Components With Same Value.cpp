#include <iostream>
#include <vector>

class Solution {
    std::vector<std::vector<int>> graph;
    int dfs(const std::vector<int>& nums, int vertex, int prev, int& components, int target) {
        int sum = nums[vertex];
        for (const auto& neighbour : graph[vertex]) {
            if (neighbour == prev) {
                continue;
            }
            sum += dfs(nums, neighbour, vertex, components, target);
        }
        if (sum == target) {
            components--;
            return 0;
        }
        return sum;
    }

public:
    int componentValue(std::vector<int>& nums, std::vector<std::vector<int>>& edges) {
        int n = nums.size();
        int sum = 0;
        for (const auto& num : nums) {
            sum += num;
        }
        graph.resize(n);

        auto add_edge = [&](int u, int v) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        };

        for (const auto& edge : edges) {
            add_edge(edge[0], edge[1]);
        }
        int ans = 0;
        for (int i = 1; i * i <= sum; i++) {
            if (sum % i == 0) {
                // check first case
                int cnt_components = i;
                int target = sum / i;
                dfs(nums, 0, -1, cnt_components, target);

                if (cnt_components == 0) {
                    ans = std::max(ans, i - 1);
                }
                // check second case
                cnt_components = sum / i;
                target = i;
                dfs(nums, 0, -1, cnt_components, target);

                if (cnt_components == 0) {
                    ans = std::max(ans, (sum / i) - 1);
                }
            }
        }
        return ans;
    }
};