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
    std::cin >> s >> q;
    int n = s.length();
    std::vector<int> arr_first(n);
    for (int i = 0; i < n; i++) {
        arr_first[i] = s[i] - 'a' + 1;
    }
    std::vector<long long> power_of_x(n + 1, 1);
    std::vector<long long> hash_prefix(n + 1, 0);
    std::vector<long long> hash_reverse(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        hash_prefix[i] = (hash_prefix[i - 1] * x + arr_first[i - 1]) % mod;
        hash_reverse[i + 1] = (hash_reverse[i] * x + arr_first[n - i - 1]) % mod;
        power_of_x[i] = (power_of_x[i - 1] * x) % mod;
    }
    for (int i = 0; i < q; i++) {
        int l = 0;
        int r = std::min(i, n - i) + 1;
        int current = 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (compute_hash())
        }
    }
    return 0;
}