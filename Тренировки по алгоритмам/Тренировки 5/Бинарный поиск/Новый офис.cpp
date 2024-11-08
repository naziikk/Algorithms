#include <iostream>
#include <vector>

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char>> square(n, std::vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> square[i][j];
        }
    }
    std::vector<std::vector<int>> dp(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        dp[i][0] = square[i][0] == '#' ? 1 : 0;
    }
    for (int i = 0; i < m; i++) {
        dp[0][i] = square[0][i] == '#' ? 1 : 0;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (square[i][j] == '#') {
                dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
            else {
                dp[i][j] = 0;
            }
        }
    }
    int l = 1;
    int r = std::min(n, m) / 2 + 1;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        bool flag = false;
        for (int i = mid; i < n - mid; i++) {
            for (int j = mid; j < m - mid; j++) {
                if (dp[i][j] >= mid) {
                    if (dp[i + mid][j] >= mid && dp[i - mid][j] >= mid &&
                    dp[i][j - mid] >= mid && dp[i][j + mid] >= mid) {
                        flag = true;
                    }
                }
            }
        }
        if (flag) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << ans;
    return 0;
}