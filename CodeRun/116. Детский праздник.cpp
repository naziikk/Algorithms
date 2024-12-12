#include <iostream>
#include <vector>

struct Assistant {
    long long time;
    long long max_consecutive;
    long long rest_time;

    Assistant() = default;

    Assistant(long long time, long long max_consecutive, long long rest_time)
    : time(time), max_consecutive(max_consecutive), rest_time(rest_time) {}
};

int main() {
    long long m, n;
    std::cin >> m >> n;
    std::vector<Assistant> assistants(n);
    for (int i = 0; i < n; i++) {
        long long time, max_consecutive, rest_time;
        std::cin >> time >> max_consecutive >> rest_time;
        assistants[i] = Assistant(time, max_consecutive, rest_time);
    }

    long long l = 0;
    long long r = 1e17;
    long long ans = -1;

    while (l <= r) {
        long long mid = (l + r) / 2;
        long long balloons = 0;

        for (int i = 0; i < n; i++) {
            long long cycle_time = assistants[i].time * assistants[i].max_consecutive + assistants[i].rest_time;
            long long full_cycles = mid / cycle_time;
            long long remaining_time = mid % cycle_time;
            long long produced = full_cycles * assistants[i].max_consecutive + std::min(remaining_time / assistants[i].time, assistants[i].max_consecutive);
            balloons += produced;
        }

        if (balloons >= m) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    std::cout << ans << '\n';

    std::vector<long long> ans_(n);
    long long balloons = 0;

    for (int i = 0; i < n; i++) {
        long long cycle_time = assistants[i].time * assistants[i].max_consecutive + assistants[i].rest_time;
        long long full_cycles = ans / cycle_time;
        long long remaining_time = ans % cycle_time;
        long long produced = full_cycles * assistants[i].max_consecutive + std::min(remaining_time / assistants[i].time, assistants[i].max_consecutive);
        ans_[i] = produced;
        balloons += produced;
    }

    while (balloons > m) {
        for (int i = 0; i < n; i++) {
            if (balloons == m) break;
            long long excess = balloons - m;
            if (ans_[i] > excess) {
                ans_[i] -= excess;
                balloons -= excess;
            } else {
                balloons -= ans_[i];
                ans_[i] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << ans_[i] << ' ';
    }
    return 0;
}