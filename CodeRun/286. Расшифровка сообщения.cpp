#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

std::string normalize(const std::string& word) {
    int shift = word[0] - 'a';
    std::string normalized;
    for (const auto& symbol : word) {
        normalized += char((symbol - 'a' - shift + 26) % 26 + 'a');
    }
    return normalized;
}

int main() {
    std::string text;
    std::getline(std::cin, text);
    std::istringstream ss(text);
    std::string word;
    std::unordered_map<std::string, std::string> pattern_map;
    while (ss >> word) {
        pattern_map[normalize(word)] = word;
    }
    int n;
    std::cin >> n;
    std::vector<std::string> results;
    for (int i = 0; i < n; i++) {
        std::cin >> word;
        std::string normalized = normalize(word);
        std::cout << pattern_map[normalized] << '\n';
    }
    return 0;
}