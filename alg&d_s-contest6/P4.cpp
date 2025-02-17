#include <iostream>
#include <vector>

struct Edge {
    int from, to, weight;

    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

std::vector<Edge> edges;
std::vector<std::vector<int>> graph;
std::vector<int> visited;

void ReplaceNegativeCycleValues(int start, std::vector<long long>& dist) {
    visited[start] = true;
    dist[start] = LLONG_MIN;
    for (const auto& neighbour : graph[start]) {
        if (!visited[neighbour]) {
            ReplaceNegativeCycleValues(neighbour, dist);
        }
    }
}

std::vector<long long> BellmanFord(int vertices, int start) {
    std::vector<long long> dist(vertices, LLONG_MAX);
    dist[start] = 0;
    int negative_cycle_start = -1;
    for (int i = 0; i < vertices; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.from] != LLONG_MAX && dist[edge.to] > dist[edge.from] + edge.weight) {
                if (i == vertices - 1) {
                    negative_cycle_start = edge.from;
                } else {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                }
            }
        }
    }
    if (negative_cycle_start != -1) {
        ReplaceNegativeCycleValues(negative_cycle_start, dist);
    }
    return dist;
}

int main() {
    int n, edges_count;
    std::cin >> n >> edges_count;
    graph.resize(n);
    visited.resize(n);
    for (int i = 0; i < edges_count; i++) {
        int from, to, dist;
        std::cin >> from >> to >> dist;
        edges.emplace_back(from, to, dist);
        graph[from].push_back(to);
    }
    std::vector<long long> dist = BellmanFord(n, 0);
    for (int i = 1; i < n; i++) {
        if (dist[i] == LLONG_MIN) {
            std::cout << "-inf\n";
        } else {
            std::cout << dist[i] << '\n';
        }
    }
    return 0;
}