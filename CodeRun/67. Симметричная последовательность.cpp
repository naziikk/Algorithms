#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

int computePalindromeSize(std::vector<int>& nums, int l, int r, int n) {
    while (l >= 0 && r < n && nums[l] == nums[r]) {
        l--;
        r++;
    }
    if (r == n) {
        return l + 1;
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < nums.size(); i++) {
        std::cin >> nums[i];
    }
    int mini = n;
    for (int i = 0; i < n; i++) {
        int l = computePalindromeSize(nums, i, i, n);
        int r = computePalindromeSize(nums, i, i + 1, n);
        if (l != -1) {
            mini = std::min(mini, l);
        }
        if (r != -1) {
            mini = std::min(mini, r);
        }
    }
    std::cout << mini << '\n';
    std::vector<int> ans;
    for (int i = 0; i < mini; i++) {
        ans.push_back(nums[i]);
    }
    std::reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << ' ';
    }
    return 0;
}