#include <iostream>
#include <vector>
#include <cmath>

static const int x = 257;
static const int mod = 1e9 + 7;

std::vector<long long> compute_hashes(const std::string& s) {
    int n = s.length();
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = s[i] - 'a' + 1;
    }
    std::vector<long long> power_of_x(n + 1, 1);
    std::vector<long long> hash(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] * x + arr[i - 1]) % mod;
        power_of_x[i] = (power_of_x[i - 1] * x) % mod;
    }
}

long long Hash(int len, int from1, int from2, const std::vector<long long>& hash, const std::vector<long long>& power_of_x) {
    return (hash[from1 + len] + hash[from2] * power_of_x[len] % mod) % mod ==
    (hash[from2 + len] + hash[from1] * power_of_x[len] % mod) % mod;
}

int main() {
    std::string s;
    int q;
    std::cin >> s >> q;
    int n = s.length();
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = s[i] - 'a' + 1;
    }
    std::vector<long long> power_of_x(n + 1, 1);
    std::vector<long long> hash(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] * x + arr[i - 1]) % mod;
        power_of_x[i] = (power_of_x[i - 1] * x) % mod;
    }
    for (int i = 0; i < q; i++) {
        int len, a, b;
        std::cin >> len >> a >> b;
        if (Hash(len, a, b, hash, power_of_x)) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }
    return 0;
}