#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>

struct Point {
    long long x;
    long long y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return x != other.x && y != other.y;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        size_t h1 = std::hash<long long>()(p.x);
        size_t h2 = std::hash<long long>()(p.y);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

double computeDistanceBetweenPoints(const Point& first, const Point& second) {
    long long dx = first.x - second.x;
    long long dy = first.y - second.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    std::unordered_set<Point, PointHash> unique_points;
    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
        unique_points.insert(points[i]);
    }
    std::unordered_map<Point, std::unordered_map<double, std::pair<int, int>>, PointHash> distances;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double dist = computeDistanceBetweenPoints(points[i], points[j]);
                distances[points[i]][dist].first++;
                if (points[i] != Point{0, 0} && unique_points.find({-points[i].x, -points[i].y}) != unique_points.end()) {
                    distances[points[i]][dist].second++;
                }
            }
        }
    }
    long long ans = 0;
    for (const auto& point : unique_points) {
        for (const auto [_, pair] : distances[point]) {
            auto [cnt, cnt_opposite] = pair;
            ans += static_cast<long long>(cnt) * (cnt - 1) / 2 - cnt_opposite / 2;
        }
    }
    std::cout << ans;
    return 0;
}
