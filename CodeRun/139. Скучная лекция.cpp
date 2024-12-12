#include <iostream>
#include <vector>

int main() {
    std::string word;
    std::cin >> word;
    int n = word.size();
    std::vector<long long> freq(26);
    for (int i = 0; i < n; i++) {
        freq[word[i] - 'a'] += (i + 1) * (n - i);
    }
    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) {
            std::cout << static_cast<char>(i + 'a') << ": " << freq[i] << '\n';
        }
    }
    return 0;
}
