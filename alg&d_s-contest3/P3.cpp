#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<std::string>> bitBucket(std::vector<std::string>& nums, int n, int k,
                                                std::vector<std::vector<std::string>>& temp) {
    if (k == n) {
        std::vector<std::vector<std::string>> buckets(10);
        for (auto& num : nums) {
            buckets[num[n] - '0'].push_back(num);
        }
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
    for (size_t i = 0; i < n; i++) {
        buckets = bitBucket(nums, n - i - 1, n - 1, buckets);
    }
    int k = 0;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < buckets[i].size(); j++) {
            nums[k] = buckets[i][j];
            k++;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    if (n == 0) {
        return 0;
    }
    std::vector<std::string> positive;
    std::vector<std::string> negative;
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        int el;
        std::cin >> el;
        if (el < 0) {
            std::string num = std::to_string(std::abs(el));
            maxLength = std::max<int>(maxLength, num.length());
            negative.push_back(num);
        } else {
            std::string num = std::to_string(el);
            maxLength = std::max<int>(maxLength, num.length());
            positive.push_back(num);
        }
    }
    for (auto& num : positive) {
        num = std::string(maxLength - num.length(), '0') + num;
    }
    for (auto& num : negative) {
        num = std::string(maxLength - num.length(), '0') + num;
    }
    radixSort(positive, maxLength);
    radixSort(negative, maxLength);
    std::reverse(negative.begin(), negative.end());
    for (int i = 0; i < negative.size(); i++) {
        std::cout << '-' << std::stoi(negative[i]) << ' ';
    }
    for (int i = 0; i < positive.size(); i++) {
        std::cout << std::stoi(positive[i]) << ' ';
    }
    return 0;
}
