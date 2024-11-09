#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::unordered_set<int> st;
    for (int i = 0; i < n; i++) {
        int el;
        std::cin >> el;
        st.insert(el);
    }
    std::vector<int> diego;
    diego.reserve(st.size());
    for (auto el : st) {
        diego.push_back(el);
    }
    std::sort(diego.begin(), diego.end());
    int k;
    std::cin >> k;
    std::vector<std::pair<int, int>> collectioners;
    for (int i = 0; i < k; i++) {
        int el;
        std::cin >> el;
        collectioners.emplace_back(el, i);
    }
    std::sort(collectioners.begin(), collectioners.end());
    int j = diego.size() - 1;
    std::vector<int> ans(k);
    for (int i = k - 1; i >= 0; i--) {
        while (j >= 0 && diego[j] >= collectioners[i].first) {
            j--;
        }
        ans[collectioners[i].second] = j + 1;
    }
    for (auto el : ans) {
        std::cout << el << '\n';
    }
    return 0;
}