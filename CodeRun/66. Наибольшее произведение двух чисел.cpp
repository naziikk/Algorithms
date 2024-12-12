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
    int first_min = INT_MAX;
    int second_min = INT_MAX;
    int first_max = INT_MIN;
    int second_max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] < first_min) {
            second_min = first_min;
            first_min = nums[i];
        } else if (nums[i] < second_min) {
            second_min = nums[i];
        }
        if (nums[i] > first_max) {
            second_max = first_max;
            first_max = nums[i];
        } else if (nums[i] > second_max) {
            second_max = nums[i];
        }
    }
    if ((long long) first_max * second_max < (long long) first_min * second_min) {
        std::cout << first_min << ' ' << second_min;
    } else {
        std::cout << second_max << ' ' << first_max;
    }
    return 0;
}