#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << 2;
        return 0;
    }
    if (n == 2) {
        std::cout << 4;
        return 0;
    }
    std::vector<long long> dp(n + 1);
    dp[1] = 2;
    dp[2] = 4;
    dp[3] = 7;
    for (int i = 4; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }
    std::cout << dp[n];
    return 0;
}

