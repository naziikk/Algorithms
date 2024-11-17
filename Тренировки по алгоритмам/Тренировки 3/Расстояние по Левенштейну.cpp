#include <iostream>
#include <vector>

int main() {
    std::string t;
    std::string s;
    std::cin >> t >> s;
    std::vector<std::vector<int>> dp(t.size() + 1, std::vector<int>(s.size() + 1, 0));
    for (int i = 0; i <= t.size(); i++) {
        dp[i][0] = i;
    }
    for (int i = 0; i < s.size(); i++) {
        dp[0][i] = i;
    }
    for (int i = 1; i <= t.size(); i++) {
        for (int j = 1; j <= s.size(); j++) {
            if (t[i - 1] == s[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
        }
    }
    std::cout << dp[t.size()][s.size()];
    return 0;
}