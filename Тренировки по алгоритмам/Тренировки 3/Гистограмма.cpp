#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main() {
    std::freopen("/Users/nazarzakrevskij/CLionProjects/AlgoAndDS_hw1/input.txt", "r", stdin);
    std::string s;
    std::unordered_map<char, int> frequency;
    while (std::getline(std::cin, s)) {
        for (auto el : s) {
            if (!std::isspace(el)) {
                frequency[el]++;
            }
        }
    }
    std::vector<std::pair<char, int>> arr;
    int maxi = 0;
    for (auto &[key,  value] : frequency) {
        maxi = std::max(maxi, value);
        arr.emplace_back(key, value);
    }
    std::sort(arr.begin(), arr.end());
    std::string ans;
    for (int i = maxi; i >= 1; i--) {
        for (int j = 0; j < arr.size(); j++) {
            if (arr[j].second >= i) {
                ans += '#';
            } else {
                ans += ' ';
            }
        }
        ans += '\n';
    }
    for (int i = 0; i < arr.size(); i++) {
        ans += arr[i].first;
    }
    std::cout << ans;
    return 0;
}