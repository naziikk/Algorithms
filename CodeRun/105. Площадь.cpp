#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    long long n, m, t;
    std::cin >> n >> m >> t;
    long long l = 0;
    long long r = std::max(n, m) / 2;
    long long full_area = n * m;
    long long ans = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long cur_n = n - 2 * mid;
        long long cur_m = m - 2 * mid;
        if (full_area - cur_m * cur_n <= t) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << ans;
    return 0;
}