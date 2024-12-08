#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    std::unordered_map<int, int> mp;
    mp[0] = 1;
    long long sum = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        if (mp.find(sum - k) != mp.end()) {
            ans += mp[sum - k];
        }
        mp[sum]++;
    }
    std::cout << ans;
    return 0;
}