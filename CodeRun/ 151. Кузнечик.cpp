#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> dp(n);
    dp[0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                dp[i] += dp[i - j];
            } else {
                break;
            }
        }
    }
    std::cout << dp.back();
    return 0;
}