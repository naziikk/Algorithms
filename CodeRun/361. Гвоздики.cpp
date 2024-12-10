#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::sort(arr.begin(), arr.end());
    std::vector<long long> dp(n, LLONG_MAX);
    dp[1] = arr[1] - arr[0];
    if (n > 2) {
        dp[2] = arr[2] - arr[0];
        for (int i = 3; i < n; i++) {
            dp[i] = std::min(dp[i - 2], dp[i - 1]) + arr[i] - arr[i - 1];
        }
    }
    std::cout << dp[n - 1];
    return 0;
}