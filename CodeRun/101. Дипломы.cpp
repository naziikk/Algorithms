#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    unsigned long long w, h, n;
    std::cin >> w >> h >> n;
    unsigned long long ans = LLONG_MAX;
    unsigned long long l = 1;
    unsigned long long r = 1e18;
    while (l <= r) {
        unsigned long long mid = (l + r) / 2;
        unsigned long long first = mid / w;
        unsigned long long second = mid / h;
        if (first * second > n) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    std::cout << ans;
    return 0;
}
