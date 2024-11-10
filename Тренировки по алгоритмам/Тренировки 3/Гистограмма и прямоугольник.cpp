#include <iostream>
#include <vector>
#include <stack>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::stack<int> st;
    arr.push_back(0);
    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            long long h = arr[st.top()];
            st.pop();
            long long w = st.empty() ? i : i - st.top() - 1;
            ans = std::max(ans, w * h);
        }
        st.push(i);
    }
    std::cout << ans;
    return 0;
}