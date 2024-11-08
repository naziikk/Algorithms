#include <iostream>
#include <vector>

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<long long> arr(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int count;
        std::cin >> count;
        arr[i] = arr[i - 1] + count;
    }
    for (int i = 0; i < m; i++) {
        long long count = 0;
        long long s = 0;
        std::cin >> count >> s;
        long long l = 0;
        long long r = n - count;
        int ans = -1;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (arr[mid + count] - arr[mid] == s) {
                ans = mid + 1;
                break;
            } else if (arr[mid + count] - arr[mid] < s) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}