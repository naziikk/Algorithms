#include <iostream>
#include <vector>
#include <map>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> mountain_chain;
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        mountain_chain.emplace_back(x, y);
    }
    std::vector<long long> left_ps(n);
    for (int i = 1; i < n; i++) {
        left_ps[i] = left_ps[i - 1] +
                std::max(0, mountain_chain[i].second - mountain_chain[i - 1].second);
    }
    std::vector<long long> right_ps(n);
    for (int i = n - 2; i >= 0; i--) {
        right_ps[i] = right_ps[i + 1] +
                std::max(0, mountain_chain[i].second - mountain_chain[i + 1].second);
    }
    int k;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        int left, right;
        std::cin >> left >> right;
        if (left < right) {
            std::cout << left_ps[right - 1] - left_ps[left - 1] << '\n';
        } else {
            std::cout << right_ps[right - 1] - right_ps[left - 1] << '\n';
        }
    }
    return 0;
}