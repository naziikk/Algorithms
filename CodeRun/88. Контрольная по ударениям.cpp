#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

std::string toLower(const std::string& word) {
    std::string lower_word = word;
    for (char& c : lower_word) {
        c = std::tolower(c);
    }
    return lower_word;
}

std::vector<std::string> split(const std::string& text) {
    std::vector<std::string> splitted_text;
    std::string word;
    for (char c : text) {
        if (std::isalpha(c)) {
            word += c;
        } else {
            if (!word.empty()) {
                splitted_text.push_back(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        splitted_text.push_back(word);
    }
    return splitted_text;
}

int main() {
    int n;
    std::cin >> n;
    std::unordered_set<std::string> all_lower;
    std::unordered_set<std::string> dictionary;
    std::string word;
    for (int i = 0; i < n; i++) {
        std::cin >> word;
        dictionary.insert(word);
        all_lower.insert(toLower(word));
    }
    std::string text;
    int mistakes = 0;
    while (std::getline(std::cin, text)) {
        std::vector<std::string> splitted_text = split(text);
        for (const auto& word : splitted_text) {
            if (all_lower.find(toLower(word)) != all_lower.end()) {
                if (dictionary.find(word) == dictionary.end()) {
                    mistakes++;
                }
            } else {
                int cnt = 0;
                for (const auto& c : word) {
                    if (std::isupper(c)) {
                        cnt++;
                    }
                }
                if (cnt != 1) {
                    mistakes++;
                }
            }
        }
    }
    std::cout << mistakes;
	return 0;
}