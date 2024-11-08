#include <iostream>
#include <stack>
#include <vector>

long long evalRPN(std::vector<std::string>& s) {
    std::stack<long long> st;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == "+" || s[i] == "-" || s[i] == "*") {
            long long f = st.top();
            st.pop();
            long long sec = st.top();
            st.pop();
            if (s[i] == "+") {
                st.push(f + sec);
            } else if (s[i] == "-") {
                st.push(sec - f);
            } else if (s[i] == "*") {
                st.push(f * sec);
            }
        } else {
           st.push(stoi(s[i]));
        }
    }
    return st.top();
}

int main() {
    std::string s;
    std::getline(std::cin, s);
    std::vector<std::string> arr;
    std::string temp;
    while (!s.empty() && s.back() == ' ') {
        s.pop_back();
    }
    for (auto el : s) {
        if (el == ' ') {
            arr.push_back(temp);
            temp.clear();
        } else {
            temp += el;
        }
    }
    arr.push_back(temp);
    std::cout << evalRPN(arr);
    return 0;
}