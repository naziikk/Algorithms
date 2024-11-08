#include <iostream>
#include <vector>
#include <stack>

struct SumStack {
    long long current_sum = 0;
    std::vector<long long> prefix_sum;
    std::stack<long long> st;

    SumStack() {
        prefix_sum.push_back(0);
    }

    long long getSum(int k) {
        return prefix_sum.back() - prefix_sum[prefix_sum.size() - k - 1];
    }

    void addElement(long long el) {
        st.push(el);
        prefix_sum.push_back(prefix_sum.back() + el);
    }

    long long popElement() {
        prefix_sum.pop_back();
        long long el = st.top();
        st.pop();
        return el;
    }
};

int main() {
    SumStack st;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string oper;
        std::cin >> oper;
        if (oper[0] == '-') {
            std::cout << st.popElement() << '\n';
        } else if (oper[0] == '+') {
            st.addElement(std::stoll(oper.substr(1)));
        } else {
            std::cout << st.getSum(std::stoi(oper.substr(1))) << '\n';
        }
    }
    return 0;
}