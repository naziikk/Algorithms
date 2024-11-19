#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> edges(n);
    for (int i = 1; i < n; i++) {
        std::cin >> edges[i];
        --edges[i];
    }
    std::vector<long long> total_earnings(n);
    std::vector<int> subtree_size(n);
    for (int i = n - 1; i > 0; i--) {
        total_earnings[i]++;
        subtree_size[i]++;
        total_earnings[edges[i]] += total_earnings[i] + subtree_size[i];
        subtree_size[edges[i]] += subtree_size[i];
    }
    total_earnings[0]++;
    subtree_size[0]++;
    for (const auto& earnings : total_earnings) {
        std::cout << earnings << " ";
    }
    return 0;
}