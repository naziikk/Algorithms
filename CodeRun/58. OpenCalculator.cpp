#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

int main() {
    std::string s;
    std::getline(std::cin, s);
    std::stringstream ss(s);
    std::unordered_set<int> st;
    while (ss >> s) {
        st.insert(std::stoi(s));
    }
    std::cin >> s;
    int ans = 0;
    for (const auto& el : s) {
        if (!st.count(el - '0')) {
            ans++;
            st.insert(el - '0');
        }
    }
    std::cout << ans;
    return 0;
}