#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int n;
    std::cin >> n;
    std::vector<long long> groups(n);
    for (int i = 0; i < n; i++) {
        std::cin >> groups[i];
    }
    std::sort(groups.begin(), groups.end());
    std::vector<long long> ps(n);
    ps[0] = groups[0];
    for (int i = 1; i < n; i++) {
        ps[i] = ps[i - 1] + groups[i];
    }
    long long ans = LLONG_MAX;
    // 1 2 5 7
    // 1 3 8 15
    for (int i = 0; i < n; i++) {
        long long temp = (i + 1) * groups[i] - ps[i];
        temp += (n - i - 1) * groups[n - 1] - (ps[n - 1] - ps[i]);
        ans = std::min(ans, temp);
    }
    std::cout << ans;
    return 0;
}
