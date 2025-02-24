#include <iostream>
#include <vector>

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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> edges(n);
    match_edges.assign(m, -1);
    visited.assign(n, 0);
    for (int i = 0; i < n; i++) {
        int neighbour;
        while (std::cin >> neighbour && neighbour != 0) {
            edges[i].push_back(neighbour - 1);
        }
    }

    int couples = 0;
    for (int i = 0; i < n; i++) {
        visited.assign(n, 0);
        if (dfs(edges, i)) {
            couples++;
        }
    }

    std::cout << couples << '\n';
    for (int i = 0; i < m; i++) {
        if (match_edges[i] != -1) {
            std::cout << match_edges[i] + 1 << ' ' << i + 1 << '\n';
        }
    }
    return 0;
}