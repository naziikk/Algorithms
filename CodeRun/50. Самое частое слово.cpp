#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> freq;
    std::string word;
    int ans_cnt = 0;
    std::string ans_word = "";
    while (std::cin >> word) {
        freq[word]++;
        if (freq[word] > ans_cnt) {
            ans_cnt = freq[word];
            ans_word = word;
        } else if (freq[word] == ans_cnt && word < ans_word) {
            ans_word = word;
        }
    }
    std::cout << ans_word;
    return 0;
}