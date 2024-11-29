#include <iostream>
#include <vector>

class Solution {
    static const int x = 257;
    static const int mod = 1e9 + 7;
    std::vector<long long> dp;

public:
    static bool isEqual(int len, int from1, int from2,
        const std::vector<long long>& hash, const std::vector<long long>& power_of_x) {
        return (hash[from1 + len] + hash[from2] * power_of_x[len] % mod) % mod ==
        (hash[from2 + len] + hash[from1] * power_of_x[len] % mod) % mod;
    }

    static void computeHashes(int n, const std::string& s, std::vector<long long>& power_of_x, std::vector<long long>& hash) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = s[i] - 'a' + 1;
        }
        for (int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] * x + arr[i - 1]) % mod;
            power_of_x[i] = (power_of_x[i - 1] * x) % mod;
        }
    }

    int memoization(const std::vector<long long>& power_of_x, const std::vector<long long>& hash, const std::string& s, int n, int i) {
        if (i >= s.length()) {
            return 0;
        }
        if (dp[i] != -1) {
            return dp[i];
        }
        int max_len = (n - i) / 2;
        int ans = 1;
        for (int len = 1; len <= max_len; ++len) {
            if (isEqual(len, i, i + len, hash, power_of_x)) {
                ans = std::max(ans, 2 + memoization(power_of_x, hash, s, n, i + len));
            }
        }
        return dp[i] = ans;
    }

    int deleteString(std::string& s) {
        int n = s.length();
        std::vector<long long> power_of_x(n + 1, 1);
        std::vector<long long> hash(n + 1, 0);
        computeHashes(n, s, power_of_x, hash);
        dp.resize(n + 1, -1);
        return memoization(power_of_x, hash, s, n, 0);
    }
};