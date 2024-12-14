#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> points(n);
    for (int i = 0; i < n; i++) {
        std::cin >> points[i];
    }
    std::sort(points.begin(), points.end());
    long long l = 0;
    long long r = points[n - 1] - points[0];
    long long ans = r;

    while (l <= r) {
        long long mid = (l + r) / 2;
        long long next = points[0] + mid;
        int cur = 1;
        for (int i = 1; i < n; i++) {
            if (points[i] > next) {
                cur++;
                next = points[i] + mid;
            }
        }
        if (cur <= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    std::cout << ans;
    return 0;
}
