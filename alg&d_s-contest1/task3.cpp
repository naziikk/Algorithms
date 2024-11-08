#include <iostream>
#include <stack>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);

    std::stack<std::string> st;
    std::stack<int> nums;
    std::string ans;
    int num = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '[') {
            nums.push(num);
            st.push(ans);
            num = 0;
            ans.clear();
        }
        else if (isdigit(s[i])) {
            num = (s[i] - '0');
        }
        else if (s[i] == ']') {
            std::string temp = ans;
            ans = st.top();
            st.pop();
            int r = nums.top();
            nums.pop();

            for (int i = 0; i < r; ++i) {
                ans += temp;
            }
        }
        else {
            ans += s[i];
        }
    }
    std::cout << ans;
    return 0;
}
close
