#include <vector>
#include <iostream>
#include <stack>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> rectangles(n);
    for (int i = 0; i < n; i++) {
        std::cin >> rectangles[i];
    }
    std::stack<int> st;
    int ans = 0;
    rectangles.push_back(0);
    for (int i = 0; i < n ; i++) {
        while (!st.empty() && rectangles[st.top()] > rectangles[i]) {
            int h = rectangles[st.top()];
            st.pop();
            int w = st.empty() ? i : i - st.top() - 1;
            ans = std::max(ans, w * h);
        }
        st.push(i);
    }
    std::cout << ans;
    return 0;
}