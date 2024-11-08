#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define int long long
struct Point {
    int x;
    int y;

    Point() : x(0), y(0) {}

    Point(int x_val, int y_val) : x(x_val), y(y_val) {}

    bool operator<(const Point& other) const {
        return x < other.x;
    }

    double computeDistance(const Point& other) const {
        double result = std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
        return result;
    }
};

double bruteForce(const std::vector<Point>& arr, int n) {
    double minDist = INT_MAX;
    for (int i = 0; i < n; ++i) {
        Point p = arr[i];
        for (int j = i + 1; j < n; ++j) {
            double dist = p.computeDistance(arr[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

double stripClosest(std::vector<Point>& arr, double d) {
    std::sort(arr.begin(), arr.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

    double minDist = d;
    for (size_t i = 0; i < arr.size(); ++i) {
        Point p = arr[i];
        for (size_t j = i + 1; j < arr.size() && (arr[j].y - arr[i].y) < minDist; ++j) {
            double dist = p.computeDistance(arr[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

double binarySplit(std::vector<Point>& arr, int l, int r) {
    if (r - l <= 3) {
        return bruteForce(std::vector<Point>(arr.begin() + l, arr.begin() + r), r - l);
    }
    int mid = (l + r) / 2;
    Point midPoint = arr[mid];
    double dl = binarySplit(arr, l, mid);
    double dr = binarySplit(arr, mid, r);
    double d = std::min(dl, dr);
    std::vector<Point> strip;
    for (int i = l; i < r; i++) {
        if (std::abs(arr[i].x - midPoint.x) < d) {
            strip.push_back(arr[i]);
        }
    }
    return std::min(d, stripClosest(strip, d));
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int x, y;
    std::vector<Point> arr;
    while (std::cin >> x >> y) {
        arr.emplace_back(x, y);
    }
    if (arr.size() == 2) {
        Point a = arr[0];
        std::cout << static_cast<int>(a.computeDistance(arr[1]));
        return 0;
    }
    std::sort(arr.begin(), arr.end(), [](const Point& a, const Point& b) {
        if (a.x == b.x) {
            return a.y < b.y;
        }
        return a.x < b.x;
    });
    double ans = binarySplit(arr, 0, static_cast<int>(arr.size()));
    std::cout << static_cast<int>(ans);
    return 0;
}