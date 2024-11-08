#include <iostream>
#include <map>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> incorrect_matches;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::pair<int, int> point1 = {x1, y1};
        std::pair<int, int> point2 = {x2, y2};
        if (point1 > point2) {
            std::swap(point1, point2);
        }
        x1 = point1.first;
        y1 = point1.second;
        x2 = point2.first;
        y2 = point2.second;
        int dx = x2 - x1;
        int dy = y2 - y1;
        incorrect_matches[{dx, dy}].emplace_back(x1, y1);
    }
    std::map<std::pair<int, int>, int> correct_matches;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::pair<int, int> point1 = {x1, y1};
        std::pair<int, int> point2 = {x2, y2};
        if (point1 > point2) {
            std::swap(point1, point2);
        }
        x1 = point1.first;
        y1 = point1.second;
        x2 = point2.first;
        y2 = point2.second;
        int dx = x2 - x1;
        int dy = y2 - y1;
        for (auto [x, y] : incorrect_matches[{dx, dy}]) {
            int mx = x1 - x;
            int my = y1 - y;
            correct_matches[{mx, my}]++;
        }
    }
    int ans = 0;
    for (auto el : correct_matches) {
        ans = std::max(ans, el.second);
    }
    std::cout << n - ans;
    return 0;
}