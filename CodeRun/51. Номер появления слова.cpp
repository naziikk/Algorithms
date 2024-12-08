#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    std::unordered_map<std::string, int> freq;
    std::string word;
    std::vector<int> ans;
    int cnt = 1;
    while (std::cin >> word) {
        ans.push_back(freq[word]);
        freq[word]++;
    }
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << " ";
    }
    return 0;
}