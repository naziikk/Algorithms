#include <iostream>
#include <stack>

bool isValid(std::string s) {
    std::stack<char> st;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            if (st.empty() || s[i] == ')' && st.top() != '('
            || s[i] == ']' && st.top() != '['
            || s[i] == '}' && st.top() != '{') {
                return false;
            }
            st.pop();
        } else {
            st.push(s[i]);
        }
    }
    return st.empty();
}

int main() {
    std::string s;
    std::cin >> s;
    if (isValid(s)) {
        std::cout << "yes";
        return 0;
    }
    std::cout << "no";
    return 0;
}