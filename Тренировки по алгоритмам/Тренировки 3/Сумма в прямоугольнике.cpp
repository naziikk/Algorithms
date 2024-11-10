#include <iostream>
#include <vector>

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<long long>> matrix(n + 1, std::vector<long long>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int value;
            std::cin >> value;
            matrix[i][j] = value + matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
        }
    }
    for (int i = 0; i < k; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        long long sum = matrix[x2][y2] - matrix[x1 - 1][y2] - matrix[x2][y1 - 1] + matrix[x1 - 1][y1 - 1];
        std::cout << sum << "\n";
    }
    return 0;
}