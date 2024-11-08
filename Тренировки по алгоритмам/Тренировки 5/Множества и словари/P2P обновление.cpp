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
        if ({x1, y1} > {x2, y2}) {
            std::swap({x1, y1}, {x2, y2});
        }
        int dx = x2 - x1;
        int dy = y2 - y1;
        incorrect_matches[{dx, dy}].emplace_back({x1, y1});
    }
    std::map<std::pair<int, int>, int> correct_matches;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if ({x1, y1} > {x2, y2}) {
            std::swap({x1, y1}, {x2, y2});
        }
        int dx = x2 - x1;
        int dy = y2 - y1;
        for (auto [x, y] : incorrect_matches) {
            int mx = x1 - x;
            int my = y1 - y;
            correct_matches[{mx, my}]++;
        }
    }
}