#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

std::vector<std::string> ans;
void backtrack(int n, std::string temp, int left, int right, std::stack<char>& st) {
    if (temp.size() == n * 2) {
        ans.push_back(temp);
        return;
    }
    if (left < n) {
        st.push('(');
        backtrack(n, temp + "(", left + 1, right, st);
        st.pop();
        st.push('[');
        backtrack(n, temp + "[", left + 1, right, st);
        st.pop();
    }
    if (right < left) {
        if (st.top() == '(') {
            st.pop();
            backtrack(n, temp + ")", left, right + 1, st);
            st.push('(');
        } else {
            st.pop();
            backtrack(n, temp + "]", left, right + 1, st);
            st.push('[');
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    if (n % 2 == 1) {
        return 0;
    }
    std::stack<char> st;
    backtrack(n / 2, "", 0, 0, st);
    for (auto str : ans) {
       std::cout << str << '\n';
    }
    return 0;
}