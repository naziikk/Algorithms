#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::sort(arr.begin(), arr.end());
    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r;
        std::cin >> l >> r;
        auto left = std::lower_bound(arr.begin(), arr.end(), l);
        auto right = std::upper_bound(arr.begin(), arr.end(), r);
        int count = right - left;
        std::cout << count << ' ';
    }
    return 0;
}