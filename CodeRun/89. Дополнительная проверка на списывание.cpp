#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cctype>
#include <algorithm>

int main() {
    int n;
    std::string case_sensitive, can_start_with_digit;
    std::cin >> n >> case_sensitive >> can_start_with_digit;
    std::unordered_set<std::string> key_words;
    for (int i = 0; i < n; ++i) {
        std::string keyword;
        std::cin >> keyword;
        if (case_sensitive == "no") {
            std::string temp = keyword;
            keyword.clear();
            for (const char& c : temp) {
                keyword += std::tolower(c);
            }
        }
        key_words.insert(keyword);
    }
    std::cin.ignore();
    std::unordered_map<std::string, int> freq;
    std::unordered_map<std::string, long long> first_ocur;
    std::string line;
    int current_position = 0;
    while (std::getline(std::cin, line)) {
        std::string identifier;
        for (char c : line) {
            current_position++;
            if (std::isalnum(c) || c == '_') {
                identifier += (case_sensitive == "no" ? std::tolower(c) : c);
            } else {
                if (!identifier.empty()) {
                    if (!(std::isdigit(identifier[0]) && can_start_with_digit == "no")
                        && !(std::isdigit(identifier[0]) && identifier.size() == 1)) {
                        if (key_words.find(identifier) == key_words.end()) {
                            if (first_ocur.find(identifier) == first_ocur.end()) {
                                first_ocur[identifier] = current_position;
                            }
                            freq[identifier]++;
                        }
                    }
                    identifier.clear();
                }
            }
        }
        if (!identifier.empty() && !(std::isdigit(identifier[0]) && can_start_with_digit == "no")
         && !(std::isdigit(identifier[0]) && identifier.size() == 1)) {
             if (key_words.find(identifier) == key_words.end()) {
                 if (first_ocur.find(identifier) == first_ocur.end()) {
                    first_ocur[identifier] = current_position;
                }
                freq[identifier]++;
             }
        }
        current_position++;
    }
    std::string answer;
    int max_frequent = 0;
    for (const auto& [word, frequency] : freq) {
        if (frequency > max_frequent) {
            max_frequent = frequency;
            answer = word;
        } else if (frequency == max_frequent) {
            if (first_ocur[word] < first_ocur[answer]) {
                answer = word;
            }
        }
    }
    std::cout << answer;
    return 0;
}
