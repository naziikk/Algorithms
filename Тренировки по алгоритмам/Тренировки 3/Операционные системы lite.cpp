#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>

bool intersect(const std::pair<long long, long long> &first, const std::pair<long long, long long> &second) {
    if (first.first <= second.second && second.first <= first.second) {
        return true;
    }
    return false;
}

int main() {
    long long m, n;
    std::cin >> m >> n;
    if (n == 0) {
        std::cout << 0;
        return 0;
    }
    std::vector<std::pair<long long, long long>> intervals(n);

    for (int i = 0; i < n; i++) {
        std::cin >> intervals[i].first >> intervals[i].second;
    }
    std::vector<bool> killed(n);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (intersect(intervals[i], intervals[j])) {
                killed[j] = true;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (killed[i] == false) {
            ans++;
        }
    }
    std::cout << ans;
    return 0;
}