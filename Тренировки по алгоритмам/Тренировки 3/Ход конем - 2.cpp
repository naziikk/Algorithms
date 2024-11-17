#include <iostream>
#include <vector>

std::string addStrings(const std::string& s, const std::string& t) {
    int i = s.length() - 1;
    int j = t.length() - 1;
    int rem = 0;
    std::string result;
    while (i >= 0 || j >= 0) {
        int sum = 0;
        if (i >= 0) {
            sum += s[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += t[j] - '0';
            j--;
        }
        sum += rem;
        rem = sum / 10;
        result += std::to_string(sum % 10);
    }
    if (rem != 0) {
        result += std::to_string(rem);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<std::pair<int, int>> distances = {{2, -1}, {2, 1}, {1, 2}, {-1, 2}};
std::vector<std::vector<std::string>> dp;

std::string memoization(int n, int m, int i, int j) {
    if (i == n - 1 && j == m - 1) {
        return "1";
    }
    if (dp[i][j] != "-1") {
        return dp[i][j];
    }
    std::string count = "0";
    for (const auto& move : distances) {
        int new_i = i + move.first;
        int new_j = j + move.second;
        if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < m) {
            count = addStrings(count, memoization(n, m, new_i, new_j));
        }
    }
    dp[i][j] = count;
    return count;
}
int main() {
    int n, m;
    std::cin >> n >> m;
    dp.assign(n, std::vector<std::string>(m, "-1"));
    std::string result = memoization(n, m, 0, 0);
    std::cout << result;
    return 0;
}