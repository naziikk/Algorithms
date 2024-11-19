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
    std::vector<long long> total_per_vertex(n);
    std::vector<int> subtree_size(n);
    for (int i = n - 1; i > 0; i--) {
        total_per_vertex[i]++;
        subtree_size[i]++;
        total_per_vertex[edges[i]] += total_per_vertex[i] + subtree_size[i];
        subtree_size[edges[i]] += subtree_size[i];
    }
    total_per_vertex[0]++;
    subtree_size[0]++;
    for (const auto& sum : total_per_vertex) {
        std::cout << sum << " ";
    }
    return 0;
}