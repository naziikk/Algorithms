#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> intervals(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;
        intervals[i] = {l, r};
    }
    std::sort(intervals.begin(), intervals.end());
    std::vector<int> temp = intervals[0];
    std::vector<std::vector<int>> merge;
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] <= temp[1]) {
            temp[1] = std::max(temp[1], intervals[i][1]);
        } else {
            merge.push_back(temp);
            temp = intervals[i];
        }
    }
    merge.push_back(temp);
    int ans = 0;
    for (const auto& interval : merge) {
        ans += interval[1] - interval[0];
    }
    std::cout << ans;
    return 0;
}