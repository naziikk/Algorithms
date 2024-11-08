#include <iostream>
#include <vector>

std::vector<int> Manacher(const std::string s, int n) {
    int l = 0;
    int r = 0;
    std::vector<int> d(n, 1);
    for (int i = 1; i < n; i++) {
        if (i < r) {
            d[i] = std::min(r - i + 1, d[r + l - i]);
        }
        while (i - d[i] >= 0 && i + d[i] < n && s[i - d[i]] == s[i + d[i]]) {
            d[i]++;
        }
        if (d[i] + i - 1 > r) {
            r = d[i] + i - 1;
            l = i - d[i] + 1;
        }
    }
    return d;
}

int main() {
    std::string s;
    std::cin >> s;
    std::string t;
    for (auto el : s) {
        t += '#';
        t += el;
    }
    t += '#';
    std::vector<int> count = Manacher(t, t.size());
    long long ans = 0;
    for (auto el : count) {
        ans += (el) / 2;
    }
    std::cout << ans;
    return 0;
}