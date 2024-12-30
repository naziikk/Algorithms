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
    int need = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == need) {
            need++;
            while (!st.empty() && st.top() == need) {
                st.pop();
                need++;
            }
        } else {
            st.push(arr[i]);
        }
    }
    std::cout << (st.empty() ? "YES" : "NO");
    return 0;
}