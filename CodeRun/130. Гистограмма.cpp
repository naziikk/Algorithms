#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Item {
    char symbol;
    int frequency;
};

int main() {
    std::string line;
    std::unordered_map<char, int> frequencies;
    while (std::getline(std::cin, line)) {
        for (const auto& symbol : line) {
            if (!std::isspace(symbol)) {
                frequencies[symbol]++;
            }
        }
    }
    std::vector<Item> arr;
    int max_frequency = 0;
    arr.reserve(frequencies.size());
    for (const auto& [symbol, frequency] : frequencies) {
        max_frequency = std::max(max_frequency, frequency);
        arr.push_back({symbol, frequency});
    }
    std::sort(arr.begin(), arr.end(), [](const Item& first, const Item& second) {
        return first.symbol < second.symbol;
    });
    std::string histogram;
    for (int i = max_frequency; i >= 1; i--) {
        for (const auto& [symbol, frequency] : arr) {
            histogram += frequency >= i ? '#' : ' ';
        }
        histogram += '\n';
    }
    for (const auto& [symbol, frequency] : arr) {
        histogram += symbol;
    }
    std::cout << histogram;
    return 0;
}