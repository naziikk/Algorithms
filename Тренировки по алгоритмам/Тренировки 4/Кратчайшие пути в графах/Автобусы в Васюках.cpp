#include <iostream>
#include <vector>
#include <set>
#include <climits>

struct Path {
    int to;
    int time_departure;
    int time_arrival;
};

struct Current {
    long long time;
    int village;

    Current(long long time, int village) : time(time), village(village) {}

    bool operator<(const Current& other) const {
        return std::tie(time, village) < std::tie(other.time, other.village);
    }
};

int main() {
    int n, start, finish;
    std::cin >> n >> start >> finish;
    int k;
    std::cin >> k;
    std::vector<std::vector<Path>> graph(n + 1);
    for (int i = 0; i < k; ++i) {
        int from, time_departure, to, time_arrival;
        std::cin >> from >> time_departure >> to >> time_arrival;
        graph[from].push_back({to, time_departure, time_arrival});
    }
    std::set<Current> st;
    st.emplace(0, start);
    std::vector<long long> dist(n + 1, LLONG_MAX);
    dist[start] = 0;
    while (!st.empty()) {
        auto [current_time, village] = *st.begin();
        st.erase(st.begin());

        for (const auto& path : graph[village]) {
            if (path.time_departure >= current_time) {
                if (dist[path.to] > path.time_arrival) {
                    st.erase({dist[path.to], path.to});
                    dist[path.to] = path.time_arrival;
                    st.emplace(path.time_arrival, path.to);
                }
            }
        }
    }
    if (dist[finish] == LLONG_MAX) {
        std::cout << -1;
    } else {
        std::cout << dist[finish];
    }

    return 0;
}