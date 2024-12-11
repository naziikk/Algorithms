#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    long long n, x, y;
    std::cin >> n >> x >> y;
    long long ans = 0;
    n--;
    long long l = 0;
    long long r = std::max(x, y) * n;
    while (l <= r) {
        long long mid = (l + r) / 2;
        if (mid / x + mid / y >= n) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    std::cout << ans + std::min(x, y);
    return 0;
}
