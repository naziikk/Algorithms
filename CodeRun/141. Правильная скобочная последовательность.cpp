#include <stack>
#include <iostream>

int main() {
    std::string sequence;
    std::cin >> sequence;
    std::stack<char> st;
    for (const auto& brace : sequence) {
        if (brace == ')' || brace == ']' || brace == '}') {
            if (st.empty() || (brace == ')' && st.top() != '(') ||
            (brace == ']' && st.top() != '[') ||
            (brace == '}' && st.top() != '{')) {
                std::cout << "no";
                return 0;
            }
            st.pop();
        } else {
            st.push(brace);
        }
    }
    if (st.empty()) {
        std::cout << "yes";
        return 0;
    }
    std::cout << "no";
    return 0;
}