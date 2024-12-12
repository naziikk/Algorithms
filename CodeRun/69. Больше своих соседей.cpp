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
    int ans = 0;
    for (int i = 1; i < nums.size() - 1; i++) {
        if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
            ans++;
        }
    }
    std::cout << ans;
	return 0;
}