#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>

struct TimePerAmount {
    int one_ticket;
    int two_tickets;
    int three_tickets;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<TimePerAmount> times(n);
    for (int i = 0; i < n; i++) {
        std::cin >> times[i].one_ticket >> times[i].two_tickets >> times[i].three_tickets;
    }
    std::vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = std::min(dp[i], dp[i - 1] + times[i - 1].one_ticket);
        if (i + 1 <= n) {
            dp[i + 1] = std::min(dp[i + 1], dp[i - 1] + times[i - 1].two_tickets);
        }
        if (i + 2 <= n) {
            dp[i + 2] = std::min(dp[i + 2], dp[i - 1] + times[i - 1].three_tickets);
        }
    }
    std::cout << dp[n];
    return 0;
}