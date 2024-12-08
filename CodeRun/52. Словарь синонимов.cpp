#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    std::unordered_map<std::string, std::string> synonyms;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string word, synonym;
        std::cin >> word >> synonym;
        synonyms[word] = synonym;
        synonyms[synonym] = word;
    }
    std::string word;
    std::cin >> word;
    std::cout << synonyms[word] << '\n';
    return 0;
}