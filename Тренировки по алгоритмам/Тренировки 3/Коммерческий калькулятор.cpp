#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

int main() {
    int n;
    std::cin >> n;
    std::priority_queue<double, std::vector<double>, std::greater<double>> pq;
    for (int i = 0; i < n; i++) {
        double el;
        std::cin >> el;
        pq.push(el);
    }
    double ans = 0;
    while (pq.size() != 1) {
        int f = pq.top();
        pq.pop();
        double current = pq.top() + f;
        pq.pop();
        ans += current * 0.05;
        pq.push(current);
    }
    std::cout << std::fixed << std::setprecision(2) << ans;
    return 0;
}