#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        arr[i] = num;
    }
    std::stack<int> st;
    int need = 1;
    int cur = 0;
    std::vector<std::pair<int, int>> res;
    std::vector<int> mas;
    for (int i = 0; i < n; i++) {
        if (arr[i] != need) {
            cur++;
            st.push(arr[i]);
        }
        else {
            cur++;
            st.push(arr[i]);
            res.emplace_back(1, cur);
            cur = 0;
            while (!st.empty() && st.top() == need) {
                mas.push_back(st.top());
                st.pop();
                cur++;
                need++;
            }
            res.emplace_back(2, cur);
            cur = 0;
        }
    }
    std::sort(arr.begin(), arr.end());
    if (mas != arr) {
        std::cout << 0;
        return 0;
    }
    for (auto [f, s] : res) {
        std::cout << f << ' ' << s << '\n';
    }
    return 0;
}