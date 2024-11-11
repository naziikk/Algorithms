#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Deadlocks {
    int current_deadlock = 0;
    int max_deadlocks = 0;
    std::priority_queue<int, std::vector<int>, std::greater<>> free_deadlocks;
    std::unordered_map<int, bool> busy_deadlocks;
    std::unordered_map<int, int> number_to_deadlock;

public:
    Deadlocks() = default;

    explicit Deadlocks(int k) : max_deadlocks(k) {}

    int comeToDeadlock(int idx) {
        if (!free_deadlocks.empty()) {
            int deadlock = free_deadlocks.top();
            free_deadlocks.pop();
            number_to_deadlock[idx] = deadlock;
            busy_deadlocks[deadlock] = true;
            return deadlock;
        }
        if (current_deadlock >= max_deadlocks) {
            return -1;
        }
        number_to_deadlock[idx] = current_deadlock;
        busy_deadlocks[current_deadlock] = true;
        current_deadlock++;
        return current_deadlock - 1;
    }

    void leaveDeadlock(int idx) {
        int deadlock = number_to_deadlock[idx];
        busy_deadlocks[deadlock] = false;
        free_deadlocks.push(deadlock);
    }
};

int main() {
    int k, n;
    std::cin >> k >> n;
    Deadlocks deadlock(k);
    std::vector<std::pair<int, int>> come(n);
    std::vector<std::pair<int, int>> leaveDeadlock(n);
    for (int i = 0; i < n; i++) {
        std::cin >> come[i].first;
        come[i].second = i;
        std::cin >> leaveDeadlock[i].first;
        leaveDeadlock[i].second = i;
    }
    std::sort(leaveDeadlock.begin(), leaveDeadlock.end());
    int j = 0;
    std::vector<int> answer(n);
    for (int i = 0; i < n; i++) {
        while (j < leaveDeadlock.size() && leaveDeadlock[j].first < come[i].first) {
            deadlock.leaveDeadlock(leaveDeadlock[j].second);
            j++;
        }
        int deadlock_number = deadlock.comeToDeadlock(come[i].second);
        if (deadlock_number == -1) {
            std::cout << 0 <<  ' ' << i + 1;
            return 0;
        }
        answer[i] = deadlock_number + 1;
    }
    for (auto el : answer) {
        std::cout << el << '\n';
    }
    return 0;
}