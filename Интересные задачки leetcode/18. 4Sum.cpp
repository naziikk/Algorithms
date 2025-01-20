#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i != 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < n; j++) {
                if (j != i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int k = j + 1;
                int r = n - 1;
                while (k < r) {
                    long long sum = (long long) nums[i] + nums[j] + nums[k] + nums[r];
                    if (sum == target) {
                        ans.push_back({nums[i], nums[j], nums[k], nums[r]});
                        k++;
                        r--;
                        while (k < r && nums[k] == nums[k - 1]) {
                            k++;
                        }
                        while (k < r && nums[r] == nums[r + 1]) {
                            r--;
                        }
                    } else if (sum < target) {
                        k++;
                    } else {
                        r--;
                    }
                }
            }
        }
        return ans;
    }
};