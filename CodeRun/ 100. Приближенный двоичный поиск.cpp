#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    for (int i = 0; i < k; i++) {
        int num;
        std::cin >> num;
        int l = 0;
        int r = n - 1;
        int closest = nums[0];
        while (l <= r) {
            int mid = (l + r) / 2;
             if (std::abs(closest - num) > std::abs(nums[mid] - num)) {
                closest = nums[mid];
            } else if (std::abs(closest - num) == std::abs(nums[mid] - num)) {
                closest = std::min(closest, nums[mid]);
            }
            if (nums[mid] == num) {
                closest = num;
                break;
            } else if (nums[mid] < num) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        std::cout << closest << '\n';
    }
    return 0;
}
