#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    std::vector<int> freq(26);
    int idx = -1;
    int max_len = 0;
    int l = 0;
    for (int i = 0; i < n; i++) {
        freq[s[i] - 'a']++;
        while (freq[s[i] - 'a'] > k) {
            freq[s[l] - 'a']--;
            l++;
        }
        if (i - l + 1 > max_len) {
            max_len = i - l + 1;
            idx = l;
        }
    }
    std::cout << max_len << ' ' << idx + 1 << '\n';
    return 0;
}