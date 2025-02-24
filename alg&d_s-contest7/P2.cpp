#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>

int bfs(int from, int to, std::vector<std::unordered_map<int, int>>& dist,
        std::vector<int>& parent, const std::vector<std::vector<int>>& graph) {
    parent.assign(parent.size(), -1);
    std::queue<std::pair<int, int>> q;
    q.emplace(from, INT_MAX);

    while (!q.empty()) {
        auto [vertex, flow] = q.front();
        q.pop();

        for (const auto& neighbour  : graph[vertex]) {
            if (parent[neighbour] == -1 && dist[vertex][neighbour] > 0) {
                parent[neighbour] = vertex;
                int new_flow = std::min(flow, dist[vertex][neighbour]);
                if (neighbour == to) {
                    return new_flow;
                }
                q.emplace(neighbour, new_flow);
            }
        }
    }

    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::unordered_map<int, int>> dist(n);
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, flow;
        std::cin >> from >> to >> flow;
        --from, --to;
        graph[from].push_back(to);
        graph[to].push_back(from);
        dist[from][to] += flow;
    }

    long long ans = 0;
    std::vector<int> parent(n);
    int min_flow;
    while (true) {
        min_flow = bfs(0, n - 1, dist, parent, graph);
        if (min_flow == 0) {
            break;
        }

        ans += min_flow;

        int idx = n - 1;
        while (idx != 0) {
            int prev = parent[idx];
            dist[prev][idx] -= min_flow;
            dist[idx][prev] += min_flow;
            idx = prev;
        }

        min_flow = INT_MAX;
    }

    std::cout << ans;
    return 0;
}