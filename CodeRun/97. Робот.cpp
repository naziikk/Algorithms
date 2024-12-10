#include <iostream>
#include <vector>

int main() {
    int k;
    std::cin >> k;
    std::string s;
    std::cin >> s;
    std::vector<int> current_strike(s.length());
    long long ans = 0;
    for (int i = k; i < s.length(); i++) {
        if (s[i] == s[i - k]) {
            current_strike[i] = current_strike[i - 1] + 1;
            ans += current_strike[i];
        } else {
            current_strike[i] = 0;
        }
    }
    std::cout << ans;
    return 0;
}
