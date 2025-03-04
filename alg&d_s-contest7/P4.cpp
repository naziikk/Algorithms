#include <vector>
#include <iostream>

std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

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
    int n, m, a, b;
    std::cin >> n >> m >> a >> b;

    std::vector<std::vector<int>> floor(n, std::vector<int>(m, -1));
    int current_number = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char current;
            std::cin >> current;
            if (current == '*') {
                floor[i][j] = current_number;
                current_number++;
            }
        }
    }

    std::vector<std::vector<int>> graph(current_number);
    match_edges.assign(current_number, -1);
    visited.assign(current_number, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (floor[i][j] == -1) {
                continue;
            }
            for (int k = 0; k < 4; k++) {
                int x = i + directions[k].first;
                int y = j + directions[k].second;
                if (x >= 0 && x < n && y >= 0 && y < m && floor[x][y] != -1) {
                    graph[floor[i][j]].push_back(floor[x][y]);
                }
            }
        }
    }

    long long total_pairs = 0;
    for (int i = 0; i < current_number; i++) {
        visited.assign(current_number, 0);
        if (dfs(graph, i)) {
            total_pairs++;
        }
    }
    long long min_cost = std::min(total_pairs / 2 * a + (current_number - total_pairs) * b, (long long) current_number * b);
    std::cout << min_cost;
    return 0;
}