#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

std::vector<int> bfs(const std::unordered_map<int, std::vector<int>>& graph, int start, int end) {
    std::queue<std::pair<int, std::vector<int>>> q;
    std::unordered_set<int> visited;

    q.push({start, {start}});
    visited.insert(start);

    while (!q.empty()) {
        auto [vertex, path] = q.front();
        q.pop();
        if (vertex == end) {
            return path;
        }
        for (const auto& neighbour : graph.at(vertex)) {
            if (visited.find(neighbour) == visited.end()) {
                visited.insert(neighbour);
                auto new_path = path;
                new_path.push_back(neighbour);
                q.push({neighbour, new_path});
            }
        }
    }
    return {};
}

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, std::vector<int>> graph;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int link;
            std::cin >> link;
            if (link == 1) {
                graph[i].push_back(j);
            }
        }
    }
    int start, end;
    std::cin >> start >> end;
    if (start == end) {
        std::cout << 0;
        return 0;
    }
    if (graph[start - 1].empty()) {
        std::cout << -1;
        return 0;
    }
    auto path = bfs(graph, start - 1, end - 1);
    if (path.empty()) {
        std::cout << -1;
        return 0;
    }
    std::cout << path.size() - 1 << '\n';
    for (const auto vertex : path) {
        std::cout << vertex + 1 << ' ';
    }
    return 0;
}
