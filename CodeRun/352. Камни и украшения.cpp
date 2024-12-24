#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    std::string s, j;
    std::cin >> j >> s;
    std::unordered_set<char> st;
    for (const auto& symb : j) {
        st.insert(symb);
    }
    int ans = 0;
    for (const auto& symb : s) {
        if (st.find(symb) != st.end()) {
            ans++;
        }
    }
    std::cout << ans;
    return 0;
}