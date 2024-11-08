#include <iostream>
#include <stack>
#include <string>

int main() {
    int n;
    std::cin >> n;
    if (n % 2 == 1) {
        std::cout << "";
        return 0;
    }
    std::string w, s;
    std::cin >> w >> s;
    std::stack<char> st;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '[') {
            st.push(s[i]);
        } else {
            st.pop();
        }
    }
    for (int i = s.length(); i < n; i++) {
        if (st.size() + i >= n) {
            if (st.top() == '(') {
                s += ')';
                st.pop();
            } else {
                s += ']';
                st.pop();
            }
        } else {
            for (int j = 0; j < 4; j++) {
                if (w[j] == ']') {
                    if (!st.empty() && st.top() == '[') {
                        s += ']';
                        st.pop();
                        break;
                    }
                } else if (w[j] == '(' || w[j] == '[') {
                    s += w[j];
                    st.push(w[j]);
                    break;
                } else {
                     if (!st.empty() && st.top() == '(') {
                        s += ')';
                        st.pop();
                        break;
                    }
                }
            }
        }
    }
    std::cout << s;
    return 0;
}