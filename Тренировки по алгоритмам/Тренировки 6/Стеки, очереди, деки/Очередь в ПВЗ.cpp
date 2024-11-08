#include <iostream>

int main() {
    long long current = 0;
    long long n, b;
    std::cin >> n >> b;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long clients = 0;
        std::cin >> clients;
        current += clients;
        if (current <= b) {
            ans += current;
            current = 0;
        } else {
            ans += current;
            current -= b;
        }
    }
    ans += current;
    std::cout << ans;
    return 0;
}