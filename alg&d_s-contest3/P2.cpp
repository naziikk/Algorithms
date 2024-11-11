#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& ans, int n) {
    int maxi = *std::max_element(ans.begin(), ans.end());
    int mini = *std::min_element(ans.begin(), ans.end());
    std::vector<int> counter_positive(maxi + 1, 0);
    std::vector<int> counter_negative(std::abs(mini) + 1, 0);
    for (int i = 0; i < n; i++) {
        if (ans[i] < 0) {
            counter_negative[std::abs(ans[i])]++;
        } else {
            counter_positive[ans[i]]++;
        }
    }
    for (int i = std::abs(mini); i >= 0; i--) {
        if (counter_negative[i]) {
            for (int j = 0; j < counter_negative[i]; j++) {
                std::cout << -i << ' ';
            }
        }
    }
    for (int i = 0; i <= maxi; i++) {
        if (counter_positive[i]) {
            for (int j = 0; j < counter_positive[i]; j++) {
                std::cout << i << ' ';
            }
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
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    countingSort(nums, n);
    return 0;
}