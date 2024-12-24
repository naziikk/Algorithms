#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    std::sort(nums.begin(), nums.end());
    int current = 1;
    int maxi = 1;
    int ans = nums[0];
    for (int i = 1; i < n; i++) {
        if (nums[i] == nums[i - 1]) {
            current++;
        } else {
            current = 1;
        }
        if (current > maxi || (current == maxi && nums[i] > ans)) {
            maxi = current;
            ans = nums[i];
        }
    }
    std::cout << ans;
    return 0;
}