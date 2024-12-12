#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::unordered_map<int, std::vector<int>> station_to_lines;
    for (int i = 0; i < m; i++) {
        int line_size;
        std::cin >> line_size;
        for (int j = 0; j < line_size; j++) {
            int vertex;
            std::cin >> vertex;
            station_to_lines[vertex].push_back(i);
        }
    }
    int a, b;
    std::cin >> a >> b;
    if (a == b) {
        std::cout << 0;
        return 0;
    }
    std::vector<std::unordered_set<int>> graph(m);
    for (const auto& [station, connected_lines] : station_to_lines) {
        for (int i = 0; i < connected_lines.size(); i++) {
            for (int j = i + 1; j < connected_lines.size(); j++) {
                graph[connected_lines[i]].insert(connected_lines[j]);
                graph[connected_lines[j]].insert(connected_lines[i]);
            }
        }
    }
    std::unordered_set<int> target = {station_to_lines[b].begin(), station_to_lines[b].end()};
    std::vector<int> start = station_to_lines[a];
    std::queue<std::pair<int, int>> q;
    std::vector<int> visited(m, 0);
    for (int i = 0; i < start.size(); i++) {
        q.emplace(start[i], 0);
        visited[start[i]] = 1;
    }
    while (!q.empty()) {
        auto [current_line, distance] = q.front();
        q.pop();
        if (target.find(current_line) != target.end()) {
            std::cout << distance;
            return 0;
        }
        for (const auto neighbour : graph[current_line]) {
            if (!visited[neighbour]) {
                q.emplace(neighbour, distance + 1);
                visited[neighbour] = 1;
            }
        }
    }
    std::cout << -1;
    return 0;
}