#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> intervals;
    for (int i = 0; i < n; i++) {
        int left, right;
        std::cin >> left >> right;
        intervals.push_back({std::min(left, right), 1});
        intervals.push_back({std::max(right, left) + 1, -1});
    }
    for (int i = 0; i < m; i++) {
        int coordinate;
        std::cin >> coordinate;
        intervals.push_back({coordinate, 0});
    }
    std::sort(intervals.begin(), intervals.end());
    int active = 0;
    std::map<int, int> mp;
    for (int i = 0; i < intervals.size(); i++) {
        if (intervals[i].type == 1) {
            active++;
        } else if (intervals[i].type == -1) {
            active--;
        } else {
            result[intervals[i].idx] = active;
        }
    }
    for (int i = 0; i < m; i++) {
        std::cout << result[i] << " ";
    }
    return 0;
}