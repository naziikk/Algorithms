#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    long long ans = 0;
    long long current = 0;
    for (int i = 0; i < n - 1; i++) {
        current = std::min<long long>(arr[i], arr[i + 1]);
        ans += current;
    }
    std::cout << ans;
    return 0;
}