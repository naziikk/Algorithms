#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#define int long long
struct DataCenter {
    int restarts;
    int active_servers;
    int idx;
    std::unordered_set<int> servers;

    bool operator<(const DataCenter& other) const {
        if (restarts * active_servers == other.restarts * other.active_servers) {
            return idx > other.idx;
        }
        return restarts * active_servers < other.restarts * other.active_servers;
    }

    bool operator>(const DataCenter& other) const {
        if (restarts * active_servers == other.restarts * other.active_servers) {
            return idx > other.idx;
        }
        return restarts * active_servers > other.restarts * other.active_servers;
    }

    bool operator!=(const DataCenter& other) const {
        return restarts != other.restarts || active_servers != other.active_servers || idx != other.idx;
    }
};

signed main() {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::priority_queue<DataCenter> max_heap;
    std::priority_queue<DataCenter, std::vector<DataCenter>, std::greater<>> min_heap;
    std::unordered_map<int, DataCenter> data_centers;
    for (int i = 0; i < n; i++) {
        DataCenter center = {0, m, i, std::unordered_set<int>()};
        data_centers[i] = center;
        max_heap.push(center);
        min_heap.push(center);
    }
    for (int i = 0; i < q; i++) {
        std::string request;
        std::cin >> request;
        if (request == "RESET") {
            int data_center_idx;
            std::cin >> data_center_idx;
            data_center_idx--;
            data_centers[data_center_idx] = {data_centers[data_center_idx].restarts + 1,
                                             m, data_center_idx, std::unordered_set<int>()};
            max_heap.push(data_centers[data_center_idx]);
            min_heap.push(data_centers[data_center_idx]);
        } else if (request == "DISABLE") {
            int data_center_idx;
            int server_idx;
            std::cin >> data_center_idx >> server_idx;
            data_center_idx--;
            server_idx--;
            if (data_centers[data_center_idx].servers.find(server_idx) == data_centers[data_center_idx].servers.end()) {
                data_centers[data_center_idx].servers.insert(server_idx);
                data_centers[data_center_idx] = {data_centers[data_center_idx].restarts,
                                                 data_centers[data_center_idx].active_servers - 1, data_center_idx, data_centers[data_center_idx].servers};
                max_heap.push(data_centers[data_center_idx]);
                min_heap.push(data_centers[data_center_idx]);
            }
        } else if (request == "GETMAX") {
            while (!max_heap.empty() && data_centers[max_heap.top().idx] != max_heap.top()) {
                max_heap.pop();
            }
            std::cout << max_heap.top().idx + 1 << '\n';
        } else {
            while (!min_heap.empty() && data_centers[min_heap.top().idx] != min_heap.top()) {
                min_heap.pop();
            }
            std::cout << min_heap.top().idx + 1 << '\n';
        }
    }
    return 0;
}