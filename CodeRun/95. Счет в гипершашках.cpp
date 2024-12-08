#include <iostream>
#include <vector>
#include <algorithm>

struct Pair {
    int value;
    int count;
};

bool operator<(long long value, const Pair& pair) {
    return value < pair.value;
}

int main() {
    long long n, k;
    std::cin >> n >> k;
    std::vector<Pair> points(n, Pair{0, 1});
    for (int i = 0; i < n; i++) {
        std::cin >> points[i].value;
    }
    std::sort(points.begin(), points.end(), [](const Pair& a, const Pair& b) {
        return a.value < b.value;
    });
    int dst = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].value == points[dst].value) {
            points[dst].count += points[i].count;
        } else {
            dst += 1;
            points[dst] = points[i];
        }
    }
    points.resize(dst + 1);
    long long answer = 0;
    std::vector<Pair> points_two_times;
    for (int i = 0; i < points.size(); i++) {
        if (points[i].count >= 3) {
            answer++;
        }
        if (points[i].count >= 2) {
            points_two_times.push_back(points[i]);
        }
    }
    // a b b
    for (int i = 0; i < points.size(); i++) {
        long long low = points[i].value;
        long long high = low * k;
        answer += 3LL * (std::upper_bound(points_two_times.begin(), points_two_times.end(), high) - std::upper_bound(points_two_times.begin(), points_two_times.end(), low));
    }
    // a a b
    for (int i = 0; i < points_two_times.size(); i++) {
        long long low = points_two_times[i].value;
        long long high = low * k;
        answer += 3LL * (std::upper_bound(points.begin(), points.end(), high) - std::upper_bound(points.begin(), points.end(), low));
    }
    // a b c
    for (int i = 0; i < points.size(); i++) {
        long long low = points[i].value;
        long long high = low * k;
        long long len = (std::upper_bound(points.begin(), points.end(), high) - std::upper_bound(points.begin(), points.end(), low));
        answer += 6LL * (len * (len - 1) / 2);
    }
    std::cout << answer;
    return 0;
}