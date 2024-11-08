#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main() {
    int k;
    std::cin >> k;
    std::string s;
    std::cin >> s;
    int l = 0;
    std::vector<int> frequency(26);
    char max_freq = s[0];
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        frequency[s[i] - 'a']++;
        if (frequency[max_freq - 'a'] < frequency[s[i] - 'a']) {
            max_freq = s[i];
        }
        if (frequency[max_freq - 'a'] + k < i - l + 1) {
            frequency[s[l] - 'a']--;
            l++;
        }
        ans = std::max(ans, i - l + 1);
    }
    std::cout << ans;
    return 0;
}