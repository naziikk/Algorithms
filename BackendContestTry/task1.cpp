#include <iostream>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include <sstream>
std::string toHex(int number) {
    std::stringstream ss;
    ss << std::uppercase << std::hex << number;
    return ss.str();
}
std::string convertData(const std::string& s) {
    std::string temp;
    std::vector<std::string> data;
    for (auto el : s) {
        if (el == ',') {
            data.push_back(temp);
            temp.clear();
        } else {
            temp += el;
        }
    }
    std::unordered_set<char> st;
    for (int i = 0; i < 3; i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            st.insert(data[i][j]);
        }
    }
    int sum = 0;
    for (int i = 3; i < 5; i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            sum += (data[i][j] - '0');
        }
    }
    sum *= 64;
    sum += (data[0][0] - 'A' + 1) * 256;
    sum += st.size();
    std::string ans = toHex(sum);
    if (ans.size() < 3) {
        ans = std::string(3 - ans.size(), '0') + ans;
    }
    return ans.substr(ans.size() - 3, 3);
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        std::cout << convertData(s) << ' ';
    }
    return 0;
}