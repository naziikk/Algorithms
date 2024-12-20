#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct Scan {
    int time;
    int type;
    int idx;

    bool operator<(const Scan& other) const {
        if (time == other.time) {
            return type < other.type;
        }
        return time < other.time;
    }
};

std::string ScanLineTest(int n) {
    std::vector<Scan> scan_line;
    int arrival_time, leaving_time;
    std::unordered_set<int> arrival_set;
    std::unordered_set<int> leaving_set;
    bool flag = false;
    for (int i = 0; i < n; i++) {
        std::cin >> arrival_time >> leaving_time;
        scan_line.push_back({arrival_time, -1, i});
        scan_line.push_back({leaving_time, 1, i});
        if (arrival_set.find(arrival_time) != arrival_set.end() ||
        leaving_set.find(leaving_time) != leaving_set.end()) {
            flag = true;
        }
        arrival_set.insert(arrival_time);
        leaving_set.insert(leaving_time);
    }
    if (flag) {
        return "Wrong Answer";
    }
    std::sort(scan_line.begin(), scan_line.end());
    if (scan_line.back().time != 10000 || scan_line[0].time != 0) {
        return "Wrong Answer";
    }
    int active_guards = 0;
    for (const auto& scan : scan_line) {
        if (scan.type == -1) {
            active_guards++;
        } else {
            active_guards--;
            if (active_guards > 1 || (active_guards == 0 && scan.idx != scan_line.back().idx)) {
                return "Wrong Answer";
            }
        }
    }
    return "Accepted";
}

int main() {
    int test_cnt;
    std::cin >> test_cnt;
    for (int i = 0; i < test_cnt; i++) {
        int n;
        std::cin >> n;
        std::cout << ScanLineTest(n) << '\n';
    }
    return 0;
}