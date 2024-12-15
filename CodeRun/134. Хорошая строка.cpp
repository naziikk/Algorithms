#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;
    std::cin >> n;
    long long ans = 0;
    long long prev = -1;
    for (int i = 0; i < n; i++) {
        long long symbol;
        std::cin >> symbol;
        if (prev == -1) {
            prev = symbol;
        } else {
            ans += std::min(prev, symbol);
            prev = symbol;
        }
    }
    std::cout << ans;
    return 0;
}