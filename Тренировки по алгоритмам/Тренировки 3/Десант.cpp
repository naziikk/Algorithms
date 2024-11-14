#include <iostream>
#include <vector>
#include <climits>

std::vector<std::vector<bool>> visited;

void dfs(std::vector<std::vector<int>>& arr, int i, int j,
         int& has_lower, bool& has_upper, int n, int m, int r, int c) {
    if (i <= 0 || j <= 0 || i >= n + 1 || j >= m + 1 || arr[i][j] != arr[r][c] || visited[i][j]) {
        return;
    }
    visited[i][j] = true;
    if (arr[i + 1][j] > arr[i][j] || arr[i - 1][j] > arr[i][j]
    || arr[i][j + 1] > arr[i][j] || arr[i][j - 1] > arr[i][j]) {
        has_upper = true;
    }
    if (arr[i + 1][j] < arr[i][j] || arr[i - 1][j] < arr[i][j]
    || arr[i][j + 1] < arr[i][j] || arr[i][j - 1] < arr[i][j]) {
        has_lower++;
    }
    dfs(arr, i + 1, j, has_lower, has_upper, n, m, r, c);
    dfs(arr, i - 1, j, has_lower, has_upper, n, m, r, c);
    dfs(arr, i, j + 1, has_lower, has_upper, n, m, r, c);
    dfs(arr, i, j - 1, has_lower, has_upper, n, m, r, c);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> arr(n + 2, std::vector<int>(m + 2, INT_MAX));
    visited.assign(n + 2, std::vector<bool>(m + 2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> arr[i][j];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!visited[i][j]) {
                int has_lower = 0;
                bool has_upper = false;
                dfs(arr, i, j, has_lower, has_upper, n, m, i, j);
                if (has_lower == 0 && has_upper) {
                    ans++;
                }
            }
        }
    }
    std::cout << ans;
    return 0;
}