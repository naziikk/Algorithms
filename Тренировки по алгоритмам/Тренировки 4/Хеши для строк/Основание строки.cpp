#include <iostream>
#include <vector>
#include <cmath>

static const int x = 257;
static const int mod = 1e9 + 7;

long long compute_hash(int len, int from, const std::vector<long long>& hash_prefix, const std::vector<long long>& power_of_x) {
    long long hash_value = (hash_prefix[from + len] - hash_prefix[from] * power_of_x[len] % mod + mod) % mod;
    return hash_value;
}

int main() {
    std::string s;
    int q;
    std::cin >> s;
    int n = s.length();
    std::vector<int> arr_first(n);
    for (int i = 0; i < n; i++) {
        arr_first[i] = s[i] - 'a' + 1;
    }
    std::vector<long long> power_of_x(n + 1, 1);
    std::vector<long long> hash_prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        hash_prefix[i] = (hash_prefix[i - 1] * x + arr_first[i - 1]) % mod;
        power_of_x[i] = (power_of_x[i - 1] * x) % mod;
    }
    for (int i = 1; i <= s.size(); i++) {
        int prev = -1;
        int j = 0;
        bool flag = true;
        while (j < s.size()) {
            if (j + i < s.size()) {
                long long hash = compute_hash(i, j, hash_prefix, power_of_x);
                if (prev == -1) {
                    prev = hash;
                } else if (prev != hash) {
                    flag = false;
                    break;
                }
                prev = hash;
                j += i;
            } else {
                if (compute_hash(s.size() - j, 0, hash_prefix, power_of_x) !=
                compute_hash(s.size() - j, j, hash_prefix, power_of_x)) {
                    flag = false;
                }
                j += i;
            }
        }
        if (flag) {
            std::cout << i;
            return 0;
        }
    }
    return 0;
}