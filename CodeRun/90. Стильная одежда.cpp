#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, m;
    std::cin >> n;
    std::vector<int> shirts(n);
    for (int i = 0; i < n; i++) {
        std::cin >> shirts[i];
    }
    std::cin >> m;
    std::vector<int> pants(m);
    for (int i = 0; i < m; i++) {
        std::cin >> pants[i];
    }
    int i = 0;
    int j = 0;
    int min_diff = 1e9;
    std::pair<int, int> ans = {-1, -1};
    while (i < n && j < m) {
        if (std::abs(shirts[i] - pants[j]) < min_diff) {
            min_diff = std::abs(shirts[i] - pants[j]);
            ans = {shirts[i], pants[j]};
        }
        if (shirts[i] < pants[j]) {
            i++;
        } else {
            j++;
        }
    }
    while (i < n) {
        if (std::abs(shirts[i] - pants[m - 1]) < min_diff) {
            min_diff = std::abs(shirts[i] - pants[m - 1]);
            ans = {shirts[i], pants[m - 1]};
        }
        i++;
    }
    while (j < m) {
        if (std::abs(shirts[n - 1] - pants[j]) < min_diff) {
            min_diff = std::abs(shirts[n - 1] - pants[j]);
            ans = {shirts[n - 1], pants[j]};
        }
        j++;
    }
    std::cout << ans.first << ' ' << ans.second;
    return 0;
}