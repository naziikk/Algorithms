#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class functions {
public:
    static void finalize(std::vector<int>& res) {
        for (int i = 0; i < res.size(); ++i) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }

    static std::vector<int> karatsuba(const std::vector<int>& f, const std::vector<int>& s) {
        int n = f.size();
        std::vector<int> ans(n * 2);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                ans[i + j] += f[i] * s[j];
            }
        }
        finalize(ans);
        return ans;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    std::string f, s;
    std::cin >> f >> s;
    int n = std::max(f.size(), s.size());
    std::vector<int> a(n);
    std::vector<int> b(n);
    for (size_t i = 0; i < f.size(); ++i) {
        a[i] = f[f.size() - 1 - i] - '0';
    }
    for (size_t i = 0; i < s.size(); ++i) {
        b[i] = s[s.size() - 1 - i] - '0';
    }
    std::vector<int> ans = functions::karatsuba(a, b);
    int j = 0;
    for (int i = ans.size() - 1; i >= 0; i--) {
        if (ans[i] != 0) {
            j = i;
            break;
        }
    }
    for (int i = j; i >= 0; --i) {
        std::cout << ans[i];
    }
    std::cout << '\n';
    return 0;
}