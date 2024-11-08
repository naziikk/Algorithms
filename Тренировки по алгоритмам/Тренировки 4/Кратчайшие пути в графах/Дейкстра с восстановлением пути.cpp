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
    std::vector<std::pair<int, std::vector<int>>> dist(n, {INT_MAX, {}});
    for (auto el : dist) {
        el.first = INT_MAX;
    }
    dist[s - 1].first = 0;
    dist[s - 1].second.push_back(s - 1);
    while (!st.empty()) {
        auto [price, from] = *st.begin();
        st.erase(st.begin());
        for (int to = 0; to < n; ++to) {
            if (graph[from][to] == INT_MAX) {
                continue;
            }
            int new_dist = dist[from].first + graph[from][to];
            if (new_dist < dist[to].first) {
                st.erase({dist[to].first, to});
                dist[to].first = new_dist;
                dist[to].second = dist[from].second;
                dist[to].second.push_back(to);
                st.emplace(dist[to].first, to);
            }
        }
    }
    if (dist[f - 1].first == INT_MAX) {
        std::cout << -1;
        return 0;
    }
    for (auto vertex : dist[f - 1].second) {
        std::cout << vertex + 1 << ' ';
    }
    return 0;
}