#include <iostream>
#include <stack>
#include <string>
#include <climits>

class Helper {
public:
    static int Prioritet(char op) {
        if (op == '+' || op == '-') {
            return 1;
        }
        if (op == '*') {
            return 2;
        }
        return 0;
    }

    static void Evaluate(std::stack<char>& operations, std::stack<long>& st) {
        if (st.empty()) {
            std::cout << "WRONG";
            exit(0);
        }
        long b = st.top();
        st.pop();
        if (st.empty()) {
            std::cout << "WRONG";
            exit(0);
        }
        long a = st.top();
        st.pop();
         if (operations.empty()) {
            std::cout << "WRONG";
            exit(0);
        }
        char op = operations.top();
        operations.pop();
        if (op == '+') {
            st.push(a + b);
        }
        if (op == '-') {
            st.push(a - b);
        }
        if (op == '*') {
            st.push(a * b);
        }
    }
};

int main() {
    int openParentheses = 0;
    std::string s;
    std::getline(std::cin, s);
    std::stack<long> st;
    std::stack<char> operations;
    for (int i = 0; i < s.length(); i++) {
        if (std::isspace(s[i])) {
            continue;
        }
        if (std::isdigit(s[i])) {
            long num = 0;
            while (i < s.length() && std::isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            i--;
            st.push(num);
        }
        else if (s[i] == '(') {
            operations.push(s[i]);
            openParentheses++;
        }
        else if (s[i] == ')') {
            if (openParentheses == 0) {
                std::cout << "WRONG\n";
                return 0;
            }
            while (!operations.empty() && operations.top() != '(') {
                Helper::Evaluate(operations, st);
            }
            if (!operations.empty()) {
                operations.pop();
                openParentheses--;
            }
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*') {
            while (!operations.empty() && Helper::Prioritet(operations.top()) >= Helper::Prioritet(s[i])) {
                Helper::Evaluate(operations, st);
            }
            operations.push(s[i]);
        }
        else {
            std::cout << "WRONG\n";
            return 0;
        }
    }
    while (!operations.empty()) {
        Helper::Evaluate(operations, st);
    }
    if (openParentheses != 0) {
        std::cout << "WRONG\n";
        return 0;
    }
    if (st.size() == 1) {
        std::cout << st.top() << "\n";
    } else {
        std::cout << "WRONG\n";
    }
    return 0;
}