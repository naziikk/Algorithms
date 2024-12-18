#include <vector>
#include <iostream>
#include <stack>
#include <unordered_set>

int main() {
    std::string first_genom;
    std::string second_genom;
    std::cin >> first_genom >> second_genom;
    std::unordered_set<std::string> second_gen_set;
    for (int i = 1; i < second_genom.length(); i++) {
        std::string current_pair;
        current_pair += second_genom[i - 1];
        current_pair += second_genom[i];
        second_gen_set.insert(current_pair);
    }
    int ans = 0;
    for (int i = 0; i < first_genom.length(); i++) {
        std::string current_pair;
        current_pair += first_genom[i - 1];
        current_pair += first_genom[i];
        if (second_gen_set.find(current_pair) != second_gen_set.end()) {
            ans++;
        }
    }
    std::cout << ans;
    return 0;
}