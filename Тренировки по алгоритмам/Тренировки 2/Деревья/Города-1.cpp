#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

std::pair<int, int> bfs_max(int n, std::vector<std::vector<int>>& graph, int start) {
    std::queue<int> vertexes;
    std::vector<int> dist(n, -1);
    vertexes.push(start);
    dist[start] = 0;
    int farthest = start;
    int maxi = 0;
    while (!vertexes.empty()) {
        auto vertex = vertexes.front();
        vertexes.pop();
        for (auto adj : graph[vertex]) {
            if (dist[adj] == -1) {
                dist[adj] = dist[vertex] + 1;
                vertexes.push(adj);
                if (dist[adj] > maxi) {
                    maxi = dist[adj];
                    farthest = adj;
                }
            }
        }
    }
    return {farthest, maxi};
}

void bfs_min(int start, std::vector<int>& dist, std::vector<std::vector<int>>& graph) {
    std::queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : graph[node]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << "0 1 1";
        return 0;
    }
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    auto [left, dist_first] = bfs_max(n, graph, 0);
    auto [right, diameter] = bfs_max(n, graph, left);
    std::vector<int> left_distances(n, -1);
    std::vector<int> right_distances(n, -1);
    bfs_min(left, left_distances, graph);
    bfs_min(right, right_distances, graph);
    std::vector<int> answer_vertexes;
    int min_dist = INT_MAX;
    for (int i = 0; i < n; i++) {
        int distance = std::max(left_distances[i], right_distances[i]);
        if (distance < min_dist) {
            min_dist = distance;
            answer_vertexes.clear();
            answer_vertexes.push_back(i + 1);
        } else if (distance == min_dist) {
            answer_vertexes.push_back(i + 1);
        }
    }
    std::cout << min_dist << ' ' << answer_vertexes.size() << ' ';
    for (const auto& vertex : answer_vertexes) {
        std::cout << vertex << ' ';
    }
    return 0;
}