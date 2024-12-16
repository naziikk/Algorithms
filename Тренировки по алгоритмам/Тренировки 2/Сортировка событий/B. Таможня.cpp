#include <iostream>
#include <vector>
#include <algorithm>

struct Scan {
    int time;
    int type;

    bool operator<(const Scan& other) const {
        if (time == other.time) {
            return type < other.type;
        }
        return time < other.time;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> intervals(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;
        intervals[i] = {l, r};
    }
    std::vector<Scan> scan_line;
    for (int i = 0; i < n; i++) {
        scan_line.push_back({intervals[i][0], 1});
        scan_line.push_back({intervals[i][0] + intervals[i][1], -1});
    }
    std::sort(scan_line.begin(), scan_line.end());
    int max_online = 0;
    int online = 0;
    for (const auto& scan : scan_line) {
        if (scan.type == -1) {
            online--;
        } else {
            online++;
        }
        max_online = std::max(online, max_online);
    }
    std::cout << max_online;
    return 0;
}