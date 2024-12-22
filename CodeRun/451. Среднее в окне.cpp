#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

bool subarraySearch(double value, const std::vector<int>& nums, int k) {
    double sum = 0;
    for (int i = 0; i < k; i++) {
        sum += nums[i] - value;
    }
    if (sum >= 0) {
        return true;
    }
    double min_sum = 0;
    double l_sum = 0;
    for (int i = k; i < nums.size(); i++) {
        sum += nums[i] - value;
        l_sum += nums[i - k] - value;
        min_sum = std::min(min_sum, l_sum);
        if (sum >= min_sum) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    double left = *std::min_element(nums.begin(), nums.end());
    double right = *std::max_element(nums.begin(), nums.end());
    double epsilon = 1e-6;
    while (right - left >= epsilon) {
        double mid = (left + right) / 2;
        if (subarraySearch(mid, nums, k)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    std::cout << std::fixed << std::setprecision(6) << left << '\n';
    return 0;
}