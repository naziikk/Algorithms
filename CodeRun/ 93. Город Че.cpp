#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    int r = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        while (r < n && nums[r] - nums[i] <= k) {
            r++;
        }
        ans += n - r;
    }
    std::cout << ans;
    return 0;
}