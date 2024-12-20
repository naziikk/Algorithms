#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
       std::cin >> nums[i];
    }
    std::sort(nums.begin(), nums.end());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (nums[i] == nums[j]) {
            i++;
        }
        i--;
        if (i - j + 1 == 1) {
            ans++;
        }
    }
    std::cout << ans;
    return 0;
}