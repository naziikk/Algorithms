#include <iostream>
#include <vector>

std::vector<std::vector<int>> dp(11, std::vector<int>(11, -1));
int dfs(std::vector<std::vector<char>>& room, int i, int j) {
    if (i < 0 || j < 0 || i >= room.size() || j >= room[0].size() || room[i][j] == '*') {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    room[i][j] = '*';
    int ans = 1;
    ans += dfs(room, i + 1, j) + dfs(room, i - 1, j) + dfs(room, i, j - 1) + dfs(room, i, j + 1);
    return dp[i][j] = ans;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<char>> room(n, std::vector<char>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> room[i][j];
        }
    }
    int i, j;
    std::cin >> i >> j;
    std::cout << dfs(room, i - 1, j - 1);
    return 0;
}
