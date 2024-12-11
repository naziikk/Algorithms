#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> intervals(m);
    for (int i = 0; i < m; i++) {
        int left, right;
        std::cin >> left >> right;
        intervals[i] = {left, right};
    }
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::pair<int, int>> merge;
    std::vector<int> temp = intervals[0];
    for (int i = 1; i < m; i++) {
        if (intervals[i][0] <= temp[1]) {
            temp[1] = std::max(temp[1], intervals[i][1]);
        } else {
            merge.push_back({temp[0], temp[1]});
            temp = intervals[i];
        }
    }
    merge.push_back({temp[0], temp[1]});
    for (const auto& [left, right] : merge) {
        n -= right - left + 1;
    }
    std::cout << n;
    return 0;
}