#include <iostream>
#include <vector>
#include <sstream>
#include <stack>

long long evaluateReversePolishNotation(const std::vector<char>& operations) {
    std::stack<long long> st;
    for (const auto& operation : operations) {
        if (std::isdigit(operation)) {
            st.push(operation - '0');
        } else {
            int first = st.top();
            st.pop();
            int second = st.top();
            st.pop();
            if (operation == '+') {
                st.push(first + second);
            } else if (operation == '-') {
                st.push(second - first);
            } else if (operation == '*') {
                st.push(second * first);
            }
        }
    }
    return st.top();
}

int main() {
    std::string s;
    std::getline(std::cin, s);
    std::stringstream ss(s);
    char operation;
    std::vector<char> operations;
    while (ss >> operation) {
        operations.push_back(operation);
    }
    std::cout << evaluateReversePolishNotation(operations);
    return 0;
}