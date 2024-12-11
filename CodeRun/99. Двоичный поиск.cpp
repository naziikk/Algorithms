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
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < k; i++) {
        int num;
        std::cin >> num;
        int l = 0;
        int r = n - 1;
        bool exists = false;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nums[mid] == num) {
                exists = true;
                break;
            } else if (nums[mid] < num) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (exists) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
