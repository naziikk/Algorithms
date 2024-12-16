#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

struct Segment {
    int coordinate;
    int type;
    int idx;

    bool operator<(const Segment& other) const {
        if (coordinate == other.coordinate) {
            return type < other.type;
        }
        return coordinate < other.coordinate;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> kitties(n);
    for (int i = 0; i < n; i++) {
        std::cin >> kitties[i];
    }
    std::vector<Segment> segments;
    for (int i = 0; i < m; i++) {
        int left, right;
        std::cin >> left >> right;
        segments.push_back({left, -1, i});
        segments.push_back({right, 1, i});
    }
    for (int i = 0; i < n; i++) {
        segments.push_back({kitties[i], 0, rand()});
    }
    std::sort(segments.begin(), segments.end());
    std::unordered_map<int, int> mp;
    std::vector<int> ans(m);
    int current = 0;
    for (const auto& segment : segments) {
        if (segment.type == -1) {
            mp[segment.idx] = current;
        } else if (segment.type == 0) {
            current++;
        } else {
            ans[segment.idx] = current - mp[segment.idx];
        }
    }
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] << ' ';
    }
    return 0;
}
