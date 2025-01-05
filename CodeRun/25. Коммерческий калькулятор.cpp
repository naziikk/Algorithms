#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

int main() {
    int n;
    std::cin >> n;
    std::priority_queue<double, std::vector<double>, std::greater<double>> pq;
    for (int i = 0; i < n; i++) {
        double num;
        std::cin >> num;
        pq.push(num);
    }
    double ans = 0;
    while (pq.size() != 1) {
        double a = pq.top();
        pq.pop();
        double b = pq.top();
        pq.pop();
        double c = a + b;
        ans += c / 100 * 5;
        pq.push(c);
    }
    std::cout << std::fixed << std::setprecision(2) << ans;
    return 0;
}