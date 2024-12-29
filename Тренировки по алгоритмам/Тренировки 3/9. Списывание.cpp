#include <iostream>
#include <vector>

bool colorGraph(int node, const std::vector<std::vector<int>>& graph, std::vector<int>& colors, int color) {
    colors[node] = color;
    for (const auto& neighbour : graph[node]) {
        if (colors[neighbour] == -1) {
            if (!colorGraph(neighbour, graph, colors, 1 - color)) {
                return false;
            }
        } else if (colors[neighbour] == color) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> tree(n + 1);
    for (int i = 0; i < m; i++) {
        int from, to;
        std::cin >> from >> to;
        tree[from].push_back(to);
        tree[to].push_back(from);
    }
    std::vector<int> colors(n + 1, -1);
    bool is_bipartite = true;
    for (int i = 1; i <= n; i++) {
        if (colors[i] == -1) {
            bool is_correct = colorGraph(i, tree, colors, 0);
            if (!is_correct) {
                is_bipartite = false;
                break;
            }
        }
    }
    if (is_bipartite) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}