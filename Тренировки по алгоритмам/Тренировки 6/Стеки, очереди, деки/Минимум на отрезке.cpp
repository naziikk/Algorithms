#include <iostream>
#include <queue>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    int l = 0;
    for (int i = 0; i < n; i++) {
        pq.emplace(arr[i], i);
        if (i - l + 1 == k) {
            std::cout << pq.top().first << '\n';
            l++;
        }
        while (!pq.empty() && pq.top().second < l) {
            pq.pop();
        }
    }
    return 0;
}