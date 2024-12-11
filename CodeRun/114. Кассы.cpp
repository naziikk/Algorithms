#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> intervals;
    int current = 0;
    for (int i = 0; i < n; i++) {
        int opening_hours, opening_minutes, closing_hours, closing_minutes;
        std::cin >> opening_hours >> opening_minutes >> closing_hours >> closing_minutes;
        int opening = opening_hours * 60 + opening_minutes;
        int closing = closing_hours * 60 + closing_minutes;
        if (opening == closing) {
            current++;
        } else if (opening > closing) {
            intervals.push_back({0, 1});
            intervals.push_back({closing, -1});
            intervals.push_back({opening, 1});
            intervals.push_back({24 * 60, -1});
        } else {
            intervals.push_back({opening, 1});
            intervals.push_back({closing, -1});
        }
    }
    if (current == n) {
        std::cout << 24 * 60;
        return 0;
    }
    std::sort(intervals.begin(), intervals.end());
    int left_bound = -1;
    int right_bound = 0;
    int ans = 0;
    for (const auto& [time, type] : intervals) {
        if (type == 1) {
            current++;
        } else {
            if (current == n) {
                right_bound = time;
                ans += right_bound - left_bound;
                left_bound = -1;
            }
            current--;
        }
        if (current == n) {
            if (left_bound == -1) {
                left_bound = time;
            }
        }
    }
    std::cout << ans;
    return 0;
}