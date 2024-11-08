#include <iostream>
#include <vector>

std::vector<std::vector<std::string>> bitBucket(std::vector<std::string>& nums, int n, int k,
                                                std::vector<std::vector<std::string>>& temp) {
    if (k == n) {
        std::vector<std::vector<std::string>> buckets(10);
        for (auto& num : nums) {
            buckets[num[n] - '0'].push_back(num);
        }
        std::cout << '\n';
        return buckets;
    }
    std::vector<std::vector<std::string>> ans(10);
    for (const auto& bucket : temp) {
        for (auto el : bucket) {
            ans[el[n] - '0'].push_back(el);
        }
    }
    return ans;
}

void radixSort(std::vector<std::string>& nums, int n) {
    std::vector<std::vector<std::string>> buckets;
    for (int i = 0; i < n; i++) {
        buckets = bitBucket(nums, n - i - 1, n - 1, buckets);
        std::cout << "Phase " << i + 1 << '\n';
        int j = 0;
        for (auto bucket : buckets) {
            std::cout << "Bucket " << j << ": ";
            if (bucket.empty()) {
                std::cout << "empty";
            } else {
                for (int k = 0; k < bucket.size(); k++) {
                    if (k != bucket.size() - 1) {
                        std::cout << bucket[k] << ", ";
                    } else {
                        std::cout << bucket[k];
                    }
                }
            }
            std::cout << '\n';
            j++;
        }
        std::cout << "**********\n";
        if (i == n - 1) {
            std::cout << "Sorted array:\n";
            int l = 0;
            std::string ans;
            for (auto bucket : buckets) {
                for (int k = 0; k < bucket.size(); k++) {
                    ans += bucket[k];
                    ans += ", ";
                }
                l++;
            }
            ans.pop_back();
            ans.pop_back();
            std::cout << ans;
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> nums;
    for (int i = 0; i < n; i++) {
        std::string el;
        std::cin >> el;
        nums.push_back(el);
    }
    std::cout << "Initial array:\n";
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            std::cout << nums[i] << ", ";
        } else {
            std::cout << nums[i];
        }
    }
    std::cout << "\n**********";
    radixSort(nums, nums[0].size());
    return 0;
}