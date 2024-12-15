#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iomanip>
#define int long long

std::vector<std::vector<std::vector<long long>>> dp;

void bfs(int vertex, const std::vector<std::unordered_set<int>>& graph, int n) {
    std::queue<std::pair<int, int>> q;
    std::vector<int> visited(n + 1, 0);
    q.emplace(vertex, 0);
    visited[vertex] = 1;
    while (!q.empty()) {
        auto [vertex_cur, dist] = q.front();
        q.pop();
        visited[vertex_cur] = 0;
        for (const auto& neighbour : graph[vertex_cur]) {
            if (dp[vertex][neighbour][0] > dp[vertex][vertex_cur][1] + 2) {
                dp[vertex][neighbour][0] = dp[vertex][vertex_cur][1] + 2;
                if (visited[neighbour] == 0) {
                    visited[neighbour] = 1;
                    q.emplace(neighbour, dist + 1);
                }
            }
            if (dp[vertex][neighbour][1] > dp[vertex][vertex_cur][0] + 2) {
                dp[vertex][neighbour][1] = dp[vertex][vertex_cur][0] + 2;
                if (visited[neighbour] == 0) {
                    visited[neighbour] = 1;
                    q.emplace(neighbour, dist + 1);
                }
            }
        }
    }
}

std::vector<int> start_edge;
std::vector<int> end_edge;

void addEdge(std::vector<std::unordered_set<int>>& graph) {
    int from, to;
    std::cin >> from >> to;
    start_edge.push_back(from);
    end_edge.push_back(to);
    graph[from].insert(to);
    graph[to].insert(from);
}

signed main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::unordered_set<int>> graph(n + 1);
    for (int i = 0; i < k; i++) {
        addEdge(graph);
    }
    int m;
    std::cin >> m;
    std::vector<int> start_positions(m + 1);
    for (int i = 1; i <= m; i++) {
        std::cin >> start_positions[i];
    }
    dp.assign(n + 1, std::vector<std::vector<long long>>(n + 1, std::vector<long long>(2, 1e16)));
    for (int i = 1; i <= n; i++) {
        dp[i][i][0] = 0;
        dp[i][i][1] = 0;
    }
    for (int i = 1; i <= m; i++) {
        bfs(start_positions[i], graph, n);
    }
    long long ans = 1e16;
    for (int i = 1; i <= n; i++) {
        long long odd = 0;
        long long even = 0;
        for (int j = 1; j <= m; j++) {
            odd = std::max(odd, dp[start_positions[j]][i][0]);
            even = std::max(even, dp[start_positions[j]][i][1]);
        }
        ans = std::min(ans, std::min(odd, even));
    }

    for (int i = 0; i < k; i++) {
        long long c = 0;
        for (int j = 1; j <= m; j++) {
            long long minValue = std::min(
                std::min(dp[start_positions[j]][start_edge[i]][0], dp[start_positions[j]][start_edge[i]][1]),
                std::min(dp[start_positions[j]][end_edge[i]][0], dp[start_positions[j]][end_edge[i]][1])
            );
            c = std::max(c, minValue + 1);
        }
        ans = std::min(ans, c);
    }
    if (ans < 1e16) {
        std::cout << std::fixed << std::setprecision(1) << ans / 2.0;
    } else {
        std::cout << -1;
    }
    return 0;
}
