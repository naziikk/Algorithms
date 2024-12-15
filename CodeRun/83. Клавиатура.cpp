#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> press_count(n);
    for (int i = 0; i < n; i++) {
        std::cin >> press_count[i];
    }
    int k;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        int press;
        std::cin >> press;
        press_count[press - 1]--;
    }
    for (int i = 0; i < n; i++) {
        if (press_count[i] < 0) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}