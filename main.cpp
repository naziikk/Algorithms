#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, r, place, k;
    std::cin >> n >> k >> r >> place;
    int peters_number = (r - 1) * 2 + (place % 2 == 0 ? 2 : 1);
    int nearest = 1e9;
    int answer_row = -1;
    int answer_place = -1;
    if (peters_number - k > 0) {
        int el = peters_number - k;
        int current_row = (el + 1) / 2;
        if (abs(r - current_row) <= nearest) {
            nearest = abs(r - current_row);
            answer_row = current_row;
            answer_place = (el % 2 == 0) ? 2 : 1;
        }
    }
    if (peters_number + k <= n) {
        int el = peters_number + k;
        int current_row = (el + 1) / 2;
        if (abs(r - current_row) <= nearest) {
            nearest = abs(r - current_row);
            answer_row = current_row;
            answer_place = (el % 2 == 0) ? 2 : 1;
        }
    }
    if (nearest == 1e9) {
        std::cout << -1;
        return 0;
    }
    std::cout << answer_row << ' ' << answer_place;
    return 0;
}