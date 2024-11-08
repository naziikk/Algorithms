#include <iostream>
#include <vector>
#include <set>
#include <climits>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<std::pair<int, long long>>> graph(n + 1);
    for (long long i = 0; i < k; i++) {
        long long from, to, cost;
        std::cin >> from >> to >> cost;
        graph[from].emplace_back(to, cost);
        graph[to].emplace_back(from, cost);
    }
    int a, b;
    std::cin >> a >> b;
    std::set<std::pair<long long, int>> st;
    st.emplace(0, a);
    std::vector<long long> dist(n + 1, LLONG_MAX);
    dist[a] = 0;
    while (!st.empty()) {
        auto [cost, from] = *st.begin();
        st.erase(*st.begin());
        for (auto paths : graph[from]) {
            if (dist[paths.first] > paths.second + dist[from]) {
                st.erase({dist[paths.first], paths.first});
                dist[paths.first] = paths.second + dist[from];
                st.emplace(dist[paths.first], paths.first);
            }
        }
    }
    if (dist[b] == LLONG_MAX) {
        std::cout << -1;
        return 0;
    }
    std::cout << dist[b];
    return 0;
}