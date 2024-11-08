#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

struct OrderData {
    int time_;
    int id_;
    char status_;

    OrderData(int time, int id, int status) : time_(time), id_(id), status_(status) {}
};

static bool Compare(const OrderData& first, const OrderData& second) {
    return first.time_ < second.time_;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<OrderData> logs;
    for (int i = 0; i < n; i++) {
        int day, hour, minute, id;
        char status;
        std::cin >> day >> hour >> minute >> id;
        std::cin >> status;
        long long minutes = day * 24 * 60 + hour * 60 + minute;
        logs.emplace_back(minutes, id, status);
    }
    std::sort(logs.begin(), logs.end(), Compare);
    std::map<int, int> answer;
    std::unordered_map<int, int> prev;
    for (auto log : logs) {
        if (log.status_ == 'A') {
            prev[log.id_] = log.time_;
        } else if (log.status_ == 'B') {
            answer[log.id_] += log.time_ - prev[log.id_];
            prev[log.id_] = log.time_;
        } else if (log.status_ == 'C') {
            answer[log.id_] += log.time_ - prev[log.id_];
            prev.erase(log.id_);
        } else {
            answer[log.id_] += log.time_ - prev[log.id_];
            prev.erase(log.id_);
        }
    }
    for (auto el : answer) {
        std::cout << el.second << ' ';
    }
    return 0;
}