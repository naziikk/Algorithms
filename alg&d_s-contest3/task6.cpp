#include <iostream>
#include <vector>
#include <algorithm>

bool canInsert(std::vector<std::string>& queens, int n, int row, int col) {
    for (int i = 0; i < n; i++) {
        if (queens[i][col] == 'Q') {
            return false;
        }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (queens[i][j] == 'Q') {
            return false;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (queens[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}

bool nQueens(int n, int i, std::vector<std::string>& queens, std::vector<int>& ans) {
    if (i == n) {
        return true;
    }
    for (int j = 0; j < n; j++) {
        if (canInsert(queens, n, i, j)) {
            queens[i][j] = 'Q';
            ans[i] = j;
            if (nQueens(n, i + 1, queens, ans)) {
                return true;
            }
            queens[i][j] = '.';
        }
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> queens(n, std::string(n, '.'));
    std::vector<int> ans(n);
    nQueens(n, 0, queens, ans);
    std::vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[ans[i]] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        std::cout << result[i] << ' ';
    }
    return 0;
}