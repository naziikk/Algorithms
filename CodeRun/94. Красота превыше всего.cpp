#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::unordered_map<int, int> mp;
    std::vector<int> trees(n);
    for (int i = 0; i < n; i++) {
        std::cin >> trees[i];
    }
    int l = 0;
    std::pair<int, int> ans = {-1, -1};
    int min_length = n + 1;
    for (int i = 0; i < n; i++) {
        mp[trees[i]]++;
        while (mp.size() >= k) {
            if (i - l + 1 < min_length) {
                min_length = i - l + 1;
                ans = {l, i};
            }
            mp[trees[l]]--;
            if (mp[trees[l]] == 0) {
                mp.erase(trees[l]);
            }
            l++;
        }
    }
    std::cout << ans.first + 1 << ' ' << ans.second + 1;
    return 0;
}