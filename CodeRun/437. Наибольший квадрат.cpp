#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> matrix[i][j];
        }
    }
    int ans = 0;
    std::pair<int, int> coordinates_answer = {0, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 1) {
                if (i == 0 || j == 0) {
                    matrix[i][j] = 1;
                } else {
                    matrix[i][j] = std::min({matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]}) + 1;
                }
                if (matrix[i][j] > ans) {
                    ans = matrix[i][j];
                    coordinates_answer = {i - matrix[i][j] + 1, j - matrix[i][j] + 1};
                }
            }
        }
    }
    std::cout << ans << '\n';
    std::cout << coordinates_answer.first + 1 << ' ' << coordinates_answer.second + 1;
    return 0;
}