#include <iostream>
#include <vector>
#include <climits>
#include <unordered_set>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> ann(n);
    for (int i = 0; i < n; i++) {
        std::cin >> ann[i];
    }
    std::vector<int> borya(m);
    for (int i = 0; i < m; i++) {
        std::cin >> borya[i];
    }
    std::unordered_set<int> a(ann.begin(), ann.end());
    std::unordered_set<int> b(borya.begin(), borya.end());
    std::sort(borya.begin(), borya.end());
    std::sort(ann.begin(), ann.end());
    std::vector<int> intersection;
    std::set_intersection(ann.begin(), ann.end(), borya.begin(), borya.end(), std::back_inserter(intersection));
    std::cout << intersection.size() << '\n';
    for (int i = 0; i < intersection.size(); i++) {
        std::cout << intersection[i] << ' ';
    }
    std::vector<int> a_diff;
    for (int i = 0; i < n; i++) {
        if (b.find(ann[i]) == b.end()) {
            a_diff.push_back(ann[i]);
        }
    }
    std::cout << '\n' << a_diff.size() << '\n';
    for (int i = 0; i < a_diff.size(); i++) {
        std::cout << a_diff[i] << ' ';
    }
    std::vector<int> b_diff;
    for (int i = 0; i < m; i++) {
        if (a.find(borya[i]) == a.end()) {
            b_diff.push_back(borya[i]);
        }
    }
    std::cout << '\n' << b_diff.size() << '\n';
    for (int i = 0; i < b_diff.size(); i++) {
        std::cout << b_diff[i] << ' ';
    }
    return 0;
}