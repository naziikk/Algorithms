#include <iostream>
#include <vector>
#include <climits>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> dp[i][j];
        }
    }
    for (int i = 1; i < n; i++) {
        dp[i][0] += dp[i - 1][0];
    }
    for (int j = 1; j < m; j++) {
        dp[0][j] += dp[0][j - 1];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] += std::min(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    std::cout << dp[n - 1][m - 1];
    return 0;
}