#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct Segment {
    int left, right;
};

int main() {
    int M;
    std::cin >> M;
    std::vector<Segment> segments;
    int l, r;
    while (true) {
        std::cin >> l >> r;
        if (l == 0 && r == 0) break;
        segments.push_back({l, r});
    }
    std::sort(segments.begin(), segments.end(), [](const Segment& a, const Segment& b) {
            return a.left < b.left;
    });
    std::vector<Segment> result;
    int current_end = 0;
    int max_end = 0;
    while (current_end < M) {
        max_end = current_end;
        Segment best_segment = {INT_MIN, INT_MIN};
        for (const auto& seg : segments) {
            if (seg.left <= current_end) {
                if (seg.right > max_end) {
                    max_end = seg.right;
                    best_segment = seg;
                }
            } else {
                break;
            }
        }
        if (best_segment.left == INT_MIN) {
            std::cout << "No solution";
            return 0;
        }
        result.push_back(best_segment);
        current_end = max_end;
    }
    std::cout << result.size() << '\n';
    for (const auto& seg : result) {
        std::cout << seg.left << " " << seg.right << '\n';
    }

    return 0;
}