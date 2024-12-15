#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> segments(n);
    for (int i = 0 ; i < n; i++) {
        std::cin >> segments[i];
    }
    long long sum = std::accumulate(segments.begin(), segments.end(), 0);
    if (sum < k) {
        std::cout << 0;
        return 0;
    }
    long long l = 1;
    long long r = sum;
    long long ans = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        int cur_segments = 0;
        for (int i = 0; i < segments.size(); i++) {
            cur_segments += segments[i] / mid;
        }
        if (cur_segments >= k) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << ans;
    return 0;
}