#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::vector<int> nums;
    while (std::cin >> n) {
        nums.push_back(n);
    }
    std::sort(nums.begin(), nums.end());
    int ans = 0;
    int l = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[l] != nums[i]) {
            l = i;
            ans++;
        }
    }
    std::cout << ans + 1;
	return 0;
}