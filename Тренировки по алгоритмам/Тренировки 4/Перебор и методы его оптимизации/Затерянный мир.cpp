#include <iostream>
#include <vector>
#include <algorithm>

bool canInsert(std::vector<std::string>& dinasaurs, int n, int row, int col) {
    for (int i = 0; i < n; i++) {
        if (dinasaurs[i][col] == 'D') {
            return false;
        }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (dinasaurs[i][j] == 'D') {
            return false;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (dinasaurs[i][j] == 'D') {
            return false;
        }
    }
    return true;
}

int ans = 0;

void nDinasaurs(int n, int i, std::vector<std::string>& dinasaurs) {
    if (i == n) {
        ans++;
        return;
    }
    for (int j = 0; j < n; j++) {
        if (canInsert(dinasaurs, n, i, j)) {
            dinasaurs[i][j] = 'D';
            nDinasaurs(n, i + 1, dinasaurs);
            dinasaurs[i][j] = '.';
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> dinasaurs(n, std::string(n, '.'));
    nDinasaurs(n, 0, dinasaurs);
    std::cout << ans;
    return 0;
}