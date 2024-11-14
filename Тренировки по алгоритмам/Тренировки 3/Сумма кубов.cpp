#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> cubes;
    for (int i = 1; i * i * i <= n; i++) {
        cubes.push_back(i * i * i);
    }
    std::vector<int> dp(n + 1, n + 1);
    dp[0] = 0;
    for (auto cube : cubes) {
        for (int i = cube; i <= n; i++) {
            dp[i] = std::min(dp[i], dp[i - cube] + 1);
        }
    }
    std::cout << dp[n];
    return 0;
}