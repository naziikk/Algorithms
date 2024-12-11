#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

std::unordered_map<int, std::vector<int>> mp;
void dfs(int vertex, const std::vector<std::unordered_set<int>>& graph, std::vector<int>& components, int component) {
    for (const auto& neighbour : graph[vertex]) {
        if (components[neighbour] == -1) {
            mp[component].push_back(neighbour);
            components[neighbour] = component;
            dfs(neighbour, graph, components, component);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::unordered_set<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int from, to;
        std::cin >> from >> to;
        if (from != to) {
            graph[from].insert(to);
            graph[to].insert(from);
        }
    }
    std::vector<int> components(n + 1, -1);
    int component = 0;
    for (int i = 1; i <= n; i++) {
        if (components[i] == -1) {
            components[i] = component;
            mp[component].push_back(i);
            dfs(i, graph, components, component);
            component++;
        }
    }
    std::cout << mp.size() << '\n';
    for (const auto& [component, vertices] : mp) {
        std::cout << vertices.size() << '\n';
        for (const auto vertex : vertices) {
            std::cout << vertex << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
