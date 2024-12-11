#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

int bfs(const std::unordered_map<int, std::vector<int>>& graph, int start, int end) {
    std::queue<std::pair<int, int>> q;
    std::unordered_set<int> visited;

    q.emplace(start, 0);
    visited.insert(start);

    while (!q.empty()) {
        auto [vertex, distance] = q.front();
        q.pop();
        if (vertex == end) {
            return distance;
        }
        for (const auto& neighbour : graph.at(vertex)) {
            if (visited.find(neighbour) == visited.end()) {
                visited.insert(neighbour);
                q.emplace(neighbour, distance + 1);
            }
        }
    }
    return -1;
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
    if (graph[start - 1].empty()) {
        std::cout << -1;
        return 0;
    }
    std::cout << bfs(graph, start - 1, end - 1);
    return 0;
}
