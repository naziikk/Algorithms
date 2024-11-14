#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

std::unordered_set<int> reachable_from;
void dfs(int v, std::unordered_map<int, std::vector<int>>& graph, std::unordered_set<int>& visited) {
    visited.insert(v);
    for (auto to : graph[v]) {
        if (visited.find(to) == visited.end()) {
            dfs(to, graph, visited);
        }
    }
    reachable_from.insert(v);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::unordered_map<int, std::vector<int>> graph;
    for (int i = 0; i < m; i++) {
        int from, to;
        std::cin >> from >> to;
        graph[to].push_back(from);
    }
    std::unordered_set<int> visited;
    dfs(1, graph, visited);
    std::vector<int> ans;
    for (auto vertex : visited) {
        ans.push_back(vertex);
    }
    std::sort(ans.begin(), ans.end());
    for (auto vertex : ans) {
        std::cout << vertex << ' ';
    }
    return 0;
}
