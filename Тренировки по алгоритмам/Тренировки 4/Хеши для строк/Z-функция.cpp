#include <iostream>
#include <vector>

std::vector<int> z_function(const std::string s, int n) {
    std::vector<int> z(n, 0);
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}

int main() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    std::vector<int> z_function_arr = z_function(s, n);
    for (auto el : z_function_arr) {
        std::cout << el << ' ';
    }
    return 0;
}