#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int findMinSimilarSunbeds(std::vector<int>& sunbeds, int n) {
    std::sort(sunbeds.begin(), sunbeds.end());
    int ans = INT_MAX;
    for (int i = 1; i < n; i++) {
        ans = std::min(ans, sunbeds[i] ^ sunbeds[i - 1]);
    }
    return ans;
}
int main() {
    int tests;
    std::cin >> tests;
    for (int i = 0; i < tests; i++) {
        int n;
        std::cin >> n;
        std::vector<int> sunbeds(n);
        for (int j = 0; j < n; j++) {
            std::cin >> sunbeds[j];
        }
        std::cout << findMinSimilarSunbeds(sunbeds, n) << '\n';
    }
    return 0;
}