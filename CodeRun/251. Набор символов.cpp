#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    std::string first, second;
    std::cin >> first >> second;
    std::vector<int> second_freq(26, 0);
    std::vector<int> first_freq(26, 0);
    int all = 0;
    for (int i = 0; i < second.size(); i++) {
        second_freq[second[i] - 'a']++;
        all++;
    }
    int cnt = 0;
    int l = 0;
    int ans = first.size() + 1;
    for (int i = 0; i < first.size(); i++) {
        first_freq[first[i] - 'a']++;
        if (second_freq[first[i] - 'a'] == 0) {
            for (int j = 0; j < 26; j++) {
                first_freq[j] = 0;
            }
            l = i + 1;
            cnt = 0;
            continue;
        }
        if (first_freq[first[i] - 'a'] == second_freq[first[i] - 'a']) {
            cnt++;
        }
        while (cnt == all) {
            ans = std::min(ans, i - l + 1);
            if (first_freq[first[l] - 'a'] == second_freq[first[l] - 'a']) {
                cnt--;
            }
            first_freq[first[l] - 'a']--;
            l++;
        }
    }
    if (ans == first.size() + 1) {
        std::cout << 0;
        return 0;
    }
    std::cout << ans;
    return 0;
}