#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    int maxi = *std::max_element(nums.begin(), nums.end());
    auto idx = std::find(nums.begin(), nums.end(), maxi) - nums.begin();
    int candidate = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i > idx && nums[i] > nums[i + 1] && nums[i] % 10 == 5) {
            candidate = std::max(candidate, nums[i]);
        }
    }
    if (candidate == 0) {
        std::cout << 0;
        return 0;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > candidate) {
            cnt++;
        }
    }
    std::cout << cnt + 1;
    return 0;
}