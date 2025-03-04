#include <iostream>
#include <vector>
#include <unordered_set>

std::vector<int> match_edges;
std::vector<int> visited;

bool dfs(const std::vector<std::vector<int>>& edges, int vertex) {
    if (visited[vertex]) {
        return false;
    }
    visited[vertex] = true;
    for (const auto& neighbour : edges[vertex]) {
        if (match_edges[neighbour] == -1 || dfs(edges, match_edges[neighbour])) {
            match_edges[neighbour] = vertex;
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::unordered_set<std::string>> components(n);
    for (int i = 0; i < n; i++) {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; j++) {
            std::string component;
            std::cin >> component;
            components[i].insert(component);
        }
    }
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                bool all_in = true;
                for (const auto& comp : components[i]) {
                    if (components[j].find(comp) == components[j].end()) {
                        all_in = false;
                        break;
                    }
                }
                if (all_in) {
                    graph[i].push_back(j);
                }
            }
        }
    }

    match_edges.resize(n, -1);
    int pairs = 0;
    for (int v = 0; v < n; ++v) {
        visited.assign(n, 0);
        if (dfs(graph, v)) {
            ++pairs;
        }
    }
    std::cout << n - pairs << '\n';
    return 0;
}