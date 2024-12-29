#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

std::vector<std::pair<char, int>> RLE(const std::string& s) {
    std::vector<std::pair<char, int>> shrink;
    int n = s.size();
    for (int i = 0; i < n;) {
        char ch = s[i];
        int cnt = 0;
        while (i < n && s[i] == ch) {
            cnt++;
            i++;
        }
        shrink.emplace_back(ch, cnt);
    }
    return shrink;
}

int main() {
    std::string s1, s2, s3;
    std::cin >> s1 >> s2 >> s3;
    if (s1.empty() && s2.empty() && s3.empty()) {
        std::cout << "";
        return 0;
    }
    if (s1.empty() || s2.empty() || s3.empty()) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }
    auto shrink1 = RLE(s1);
    auto shrink2 = RLE(s2);
    auto shrink3 = RLE(s3);
    if (shrink1.size() != shrink2.size() || shrink2.size() != shrink3.size()) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }
    std::string ans;
    int n = shrink1.size();
    for (int i = 0; i < n; i++) {
        char ch1 = shrink1[i].first, ch2 = shrink2[i].first, ch3 = shrink3[i].first;
        int cnt1 = shrink1[i].second, cnt2 = shrink2[i].second, cnt3 = shrink3[i].second;
        if (ch1 != ch2 || ch2 != ch3) {
            std::cout << "IMPOSSIBLE";
            return 0;
        }
        int current = std::min(std::min(std::abs(cnt1 - cnt2) + std::abs(cnt1 - cnt3),
                                        std::abs(cnt2 - cnt1) + std::abs(cnt2 - cnt3)),
                               std::abs(cnt3 - cnt1) + std::abs(cnt3 - cnt2));
        if (std::abs(cnt1 - cnt2) + std::abs(cnt1 - cnt3) == current) {
            for (int h = 0; h < cnt1; h++) {
                ans += ch1;
            }
        } else if (std::abs(cnt2 - cnt1) + std::abs(cnt2 - cnt3) == current) {
            for (int h = 0; h < cnt2; h++) {
                ans += ch1;
            }
        } else {
            for (int h = 0; h < cnt3; h++) {
                ans += ch1;
            }
        }
    }
    std::cout << ans;
    return 0;
}