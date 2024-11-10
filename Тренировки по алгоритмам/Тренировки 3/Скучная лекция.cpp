#include <iostream>
#include <vector>

int main() {
    std::string word;
    std::cin >> word;
    std::vector<long long> frequency(26);
    for (long long i = 0; i < word.size(); i++) {
        frequency[word[i] - 'a'] += (i + 1) * (word.size() - i);
    }
    for (int i = 0; i < 26; i++) {
        if (frequency[i] != 0) {
            std::cout << static_cast<char>(i + 'a') << ": " << frequency[i] << '\n';
        }
    }
    return 0;
}