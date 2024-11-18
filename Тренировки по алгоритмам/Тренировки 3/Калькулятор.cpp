#include <iostream>
#include <vector>
#include <climits>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, std::vector<int>>> dp(n + 1);
    for (int i = 2; i <= n; i++) {
        dp[i] = {INT_MAX, {0}};
    }
    dp[1].first = 1;
    dp[1].second.push_back(1);
    for (int i = 1; i <= n; i++) {
        if (i * 2 <= n && dp[i * 2].first > dp[i].first + 1) {
            dp[i * 2].first = dp[i].first + 1;
            dp[i * 2].second.clear();
            dp[i * 2].second = dp[i].second;
            dp[i * 2].second.push_back(i * 2);
        }
        if (i * 3 <= n && dp[i * 3].first > dp[i].first + 1) {
            dp[i * 3].first = dp[i].first + 1;
            dp[i * 3].second.clear();
            dp[i * 3].second = dp[i].second;
            dp[i * 3].second.push_back(i * 3);
        }
        if (i + 1 <= n && dp[i + 1].first > dp[i].first + 1) {
            dp[i + 1].first = dp[i].first + 1;
            dp[i + 1].second.clear();
            dp[i + 1].second = dp[i].second;
            dp[i + 1].second.push_back(i + 1);
        }
    }
    std::cout << dp[n].first - 1 << '\n';
    for (auto move : dp[n].second) {
        std::cout << move << ' ';
    }
    return 0;
}