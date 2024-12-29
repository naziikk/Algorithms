#include <vector>

class Solution {
    const int mod = 1e9 + 7;
    std::vector<std::vector<int>> dp;

    int memoization(int i, int j, std::vector<std::vector<int>>& idx_frequencies, const string& target) {
        if (j == target.size()) {
            return 1;
        }
        if (i == idx_frequencies.size()) {
            return 0;
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        long long cnt = memoization(i + 1, j, idx_frequencies, target);
        if (idx_frequencies[i][target[j] - 'a'] > 0) {
            cnt += idx_frequencies[i][target[j] - 'a'] * 1LL * memoization(i + 1, j + 1, idx_frequencies, target) % mod;
        }
        return dp[i][j] = cnt % mod;
    }

public:
    int numWays(std::vector<std::string>& words, const std::string target) {
        std::vector<std::vector<int>> idx_frequencies(words[0].size(), std::vector<int>(26));
        for (const auto& word : words) {
            for (int i = 0; i < word.size(); i++) {
                idx_frequencies[i][word[i] - 'a']++;
            }
        }
        dp.assign(words[0].size() + 1, std::vector<int>(target.size() + 1, -1));
        return memoization(0, 0, idx_frequencies, target);
    }
};