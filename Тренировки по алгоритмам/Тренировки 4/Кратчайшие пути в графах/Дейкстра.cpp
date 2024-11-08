#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <climits>

int main() {
    int n, s, f;
    std::cin >> n >> s >> f;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> graph[i][j];
            if (graph[i][j] == -1) {
                graph[i][j] = INT_MAX;
            }
        }
    }
    std::set<std::pair<int, int>> st;
    st.emplace(0, s - 1);
    std::vector<int> dist(n, INT_MAX);
    dist[s - 1] = 0;
    while (!st.empty()) {
        auto [price, from] = *st.begin();
        st.erase(st.begin());
        for (int to = 0; to < n; ++to) {
            if (graph[from][to] == INT_MAX) {
                continue;
            }
            int new_dist = dist[from] + graph[from][to];
            if (new_dist < dist[to]) {
                st.erase({dist[to], to});
                dist[to] = new_dist;
                st.emplace(dist[to], to);
            }
        }
    }
    if (dist[f - 1] == INT_MAX) {
        std::cout << -1;
        return 0;
    }
    std::cout << dist[f - 1];
    return 0;
}