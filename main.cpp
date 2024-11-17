#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> distances = {{2, -1}, {2, 1}, {1, 2}, {-1, 2}};
std::vector<std::vector<long long>> dp;

long long memoization(int n, int m, int i, int j) {
    if (i == n - 1 && j == m - 1) {
        return 1;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    long long count = 0;
    for (const auto& move : distances) {
        int new_i = i + move.first;
        int new_j = j + move.second;
        if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < m) {
            count += memoization(n, m, new_i, new_j);
        }
    }
    dp[i][j] = count;
    return count;
}
int main() {
    int n, m;
    std::cin >> n >> m;
    dp.assign(n, std::vector<long long>(m, -1));
    long long result = memoization(n, m, 0, 0);
    std::cout << result;
    return 0;
}