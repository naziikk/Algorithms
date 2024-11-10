#include <iostream>
#include <vector>

std::vector<int> CalculateResult(const std::vector<std::pair<int, int>>& points) {
    int leftmost_x = 1e9;
    int rightmost_x = -1e9;
    int highest_y = -1e9;
    int lowest_y = 1e9;
    for (int i = 0; i < points.size(); i++) {
        leftmost_x = std::min(leftmost_x, points[i].first);
        rightmost_x = std::max(rightmost_x, points[i].first);
        highest_y = std::max(highest_y, points[i].second);
        lowest_y = std::min(lowest_y, points[i].second);
    }
    std::vector<int> ans = {leftmost_x, lowest_y, rightmost_x, highest_y};
    return ans;
}

int main() {
    int k;
    std::cin >> k;
    std::vector<std::pair<int, int>> points(k);
    for (int i = 0; i < k; i++) {
        std::cin >> points[i].first >> points[i].second;
    }
    auto answer = CalculateResult(points);
    for (int i = 0; i < 4; i++) {
        std::cout << answer[i] << ' ';
    }
    return 0;
}