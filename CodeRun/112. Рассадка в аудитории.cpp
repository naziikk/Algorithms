#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

int main() {
    int n, d;
    std::cin >> n >> d;
    std::vector<std::pair<int, int>> students(n);
    for (int i = 0; i < n; i++) {
        std::cin >> students[i].first;
        students[i].second = i;
    }
    std::sort(students.begin(), students.end());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>>> less_than_d;
    std::set<int> st;
    std::vector<int> ans(n);
    int current = 1;
    for (int i = 0; i < n; i++) {
        while (!less_than_d.empty() && students[i].first - less_than_d.top().first > d) {
            st.insert(less_than_d.top().second);
            less_than_d.pop();
        }
        if (!st.empty()) {
            ans[students[i].second] = *st.begin();
            st.erase(st.begin());
            less_than_d.push({students[i].first, ans[students[i].second]});
        } else {
            ans[students[i].second] = current;
            less_than_d.push({students[i].first, current});
            current++;
        }
    }
    std::cout << current - 1 << '\n';
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << ' ';
    }
    return 0;
}