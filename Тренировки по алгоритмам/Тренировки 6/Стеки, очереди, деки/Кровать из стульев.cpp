#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

int main() {
    long long n, H;
    std::cin >> n >> H;
    std::vector<std::pair<long long, long long>> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i].first;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i].second;
        if (arr[i].second >= H) {
            std::cout << 0;
            return 0;
        }
    }
    std::sort(arr.begin(), arr.end());
    int l = 0;
    long long ans = LLONG_MAX;
    std::priority_queue<std::pair<long long, long long>, std::vector<std::pair<long long, long long>>> pq;
    long long current_width = 0;
    for (int i = 0; i < n; i++) {
        current_width += arr[i].second;
        if (i != 0) {
            pq.emplace(arr[i].first - arr[i - 1].first, i - 1);
        }
        while (current_width >= H) {
            if (!pq.empty()) {
                ans = std::min(ans, pq.top().first);
            }
            current_width -= arr[l].second;
            while (!pq.empty() && pq.top().second <= l) {
                pq.pop();
            }
            l++;
        }
    }
    std::cout << ans;
    return 0;
}