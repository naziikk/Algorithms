#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int main() {
    std::queue<int> first;
    std::queue<int> second;
    for (int i = 0; i < 5; i++) {
        int el;
        std::cin >> el;
        first.push(el);
    }
    for (int i = 0; i < 5; i++) {
        int el;
        std::cin >> el;
        second.push(el);
    }
    for (int i = 0; i < 1e6; i++) {
        auto first_card = first.front();
        first.pop();
        auto second_card = second.front();
        second.pop();
        if (first_card > second_card) {
            if (first_card == 9 && second_card == 0) {
                second.push(first_card);
                second.push(second_card);
            } else {
                first.push(first_card);
                first.push(second_card);
            }
        } else if (second_card > first_card) {
            if (second_card == 9 && first_card == 0) {
                first.push(first_card);
                first.push(second_card);
            } else {
                second.push(first_card);
                second.push(second_card);
            }
        }
        if (first.empty()) {
            std::cout << "second" << ' ' << i + 1;
            return 0;
        } else if (second.empty()) {
            std::cout << "first" << ' ' << i + 1;
            return 0;
        }
    }
    std::cout << "botwa";
    return 0;
}
