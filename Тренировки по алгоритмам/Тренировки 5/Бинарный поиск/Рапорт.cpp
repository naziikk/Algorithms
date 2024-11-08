#include <iostream>
#include <vector>

int main() {
    long long w, n, m;
    std::cin >> w >> n >> m;
    long long l = 0;
    std::vector<long long> arr_n(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr_n[i];
        l = std::max(l, arr_n[i]);
    }
    long long r = w;
    std::vector<long long> arr_m(m);
    for (int i = 0; i < m; i++) {
        std::cin >> arr_m[i];
        r = std::min(r, w - arr_m[i]);
    }
    int ans = 1e9;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long current = 0;
        long long len_first = 1;
        for (int i = 0; i < n; i++) {
            if (current + arr_n[i] <= mid) {
                current += arr_n[i] + 1;
            } else {
                current = arr_n[i] + 1;
                len_first++;
            }
        }
        current = 0;
        long long second = w - mid;
        long long len_second = 1;
        for (int i = 0; i < m; i++) {
            if (current + arr_m[i] <= second) {
                current += arr_m[i] + 1;
            } else {
                current = arr_m[i] + 1;
                len_second++;
            }
        }
        if (std::max(len_first, len_second) < ans) {
            ans = std::max(len_first, len_second);
            if (len_first < len_second) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if (len_first < len_second) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
    std::cout << ans;
    return 0;
}