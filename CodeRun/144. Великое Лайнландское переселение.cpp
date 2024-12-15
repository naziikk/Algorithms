#include <iostream>
#include <stack>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> towns(n);
    for (int i = 0; i < n; i++) {
        std::cin >> towns[i];
    }
    std::stack<int> st;
    std::vector<int> ans(n, - 1);
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && towns[st.top()] >= towns[i]) {
            st.pop();
        }
        if (!st.empty()) {
            ans[i] = st.top();
        }
        st.push(i);
    }
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << ' ';
    }
    return 0;
}