#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums1(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums1[i];
    }
    int m;
    std::cin >> m;
    std::vector<int> nums2(m);
    for (int i = 0; i < m; i++) {
        std::cin >> nums2[i];
    }
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int i = n;
    int j = m;
    std::vector<int> lcs;
    while (i > 0 && j > 0) {
        if (nums1[i - 1] == nums2[j - 1]) {
            lcs.push_back(nums1[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] == dp[i][j]) {
            i--;
        } else {
            j--;
        }
    }
    std::reverse(lcs.begin(), lcs.end());
    for (auto el : lcs) {
        std::cout << el << ' ';
    }
    return 0;
}

