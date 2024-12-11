#include <iostream>
#include <vector>
#include <unordered_set>

void dfs(int vertex, const std::vector<std::unordered_set<int>>& graph, std::vector<int>& components, int component) {
    for (const auto& neighbour : graph[vertex]) {
        if (components[neighbour] == -1) {
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
            dfs(i, graph, components, component);
            component++;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (components[i] == components[1]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        if (components[i] == components[1]) {
            std::cout << i << ' ';
        }
    }
    return 0;
}
