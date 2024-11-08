#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    if (n == 1) {
        std::cout << 1;
        return 0;
    }
    long long l = 0;
    long long r = n;
    long long ans = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long current = 0;

        for (long long i = 1; i <= mid; i++) {
            if (i == mid) {
                current += i * (mid - i + 1) + i - 1;
            } else {
                current += i * (mid - i + 1) + i;
            }
            if (current > n) {
                break;
            }
        }
        if (current <= n) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    std::cout << ans;
    return 0;
}