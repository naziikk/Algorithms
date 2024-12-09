#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<std::vector<long long>> pleasure(n, std::vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> pleasure[i][j];
        }
    }
    std::vector<std::vector<long long>> anti_pleasure(n, std::vector<long long>(m));
    std::vector<std::vector<long long>> result(n, std::vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> anti_pleasure[i][j];
            result[i][j] = std::max(pleasure[i][j], anti_pleasure[i][j]);
        }
    }
    std::vector<long long> student_idx(m);
    for (int j = 0; j < m; j++) {
        long long idx = -1;
        long long max_pleasure = LLONG_MIN;
        for (long long i = 0; i < n; i++) {
            if (pleasure[i][j] - anti_pleasure[i][j] > max_pleasure) {
                max_pleasure = pleasure[i][j] - anti_pleasure[i][j];
                idx = i;
            }
        }
        student_idx[j] = idx;
    }
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (student_idx[i] == j) {
                ans += pleasure[j][i];
            } else {
                ans += result[j][i];
            }
        }
    }
    std::cout << ans;
    return 0;
}