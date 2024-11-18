#include <iostream>
#include <vector>
#include <climits>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<long long, std::string>>> dp(n, std::vector<std::pair<long long, std::string>>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> dp[i][j].first;
        }
    }
    for (int i = 1; i < n; i++) {
        dp[i][0].first += dp[i - 1][0].first;
        dp[i][0].second = dp[i - 1][0].second + "D";
    }
    for (int j = 1; j < m; j++) {
        dp[0][j].first += dp[0][j - 1].first;
        dp[0][j].second = dp[0][j - 1].second + "R";
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (dp[i - 1][j].first > dp[i][j - 1].first) {
                dp[i][j].first += dp[i - 1][j].first;
                dp[i][j].second = dp[i - 1][j].second + "D";
            } else {
                dp[i][j].first += dp[i][j - 1].first;
                dp[i][j].second = dp[i][j - 1].second + "R";
            }
        }
    }
    std::cout << dp[n - 1][m - 1].first << '\n';
    for (auto move : dp[n - 1][m - 1].second) {
        std::cout << move << ' ';
    }
    return 0;
}