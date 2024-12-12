#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>
#include <algorithm>

int main() {
    int n;
    std::vector<int> nums;
    while (std::cin >> n) {
       nums.push_back(n);
    }
    n = nums.size();
    std::sort(nums.begin(), nums.end());
    if ((long long) nums[0] * nums[1] * nums[n - 1] < (long long) nums[n - 1] * nums[n - 2] * nums[n - 3]) {
        std::cout << nums[n - 1] << ' ' << nums[n - 2] << ' ' << nums[n - 3];
    } else {
        std::cout << nums[0] << ' ' <<  nums[1] << ' ' << nums[n - 1];
    }
    return 0;
}