class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int min_v = nums[n - 1];
        int l = 0;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] > min_v) {
                l = i;
            } else {
                min_v = nums[i];
            }
        }
        int max_v = nums[0];
        int r = -1;
        for (int i = 1; i < n; i++) {
            if (nums[i] < max_v) {
                r = i;
            } else {
                max_v = nums[i];
            }
        }
        return r - l + 1;
    }
};