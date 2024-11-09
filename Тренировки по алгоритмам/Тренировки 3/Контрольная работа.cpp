#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>

int main() {
    int n, r, place, k;
    std::cin >> n >> k >> r >> place;
    std::unordered_map<int, std::pair<int, int>> mp;
    int current = 1;
    for (int i = 1; i <= n; i++) {
        mp[i] = {current % k, i / 2 + i % 2};
        current++;
    }

    int need = mp[2 * (r - 1) + place % 2].first;
    int peters_r = r;
    int pre_ans = INT_MAX;
    int number = -1;
    int ryad = -1;
    for (auto el : mp) {
        if (el.first != (2 * (r - 1) + place % 2) && el.second.first == need) {
            if (std::abs(peters_r - el.second.second) <= pre_ans) {
                if (std::abs(peters_r - el.second.second) == pre_ans) {
                    pre_ans = std::abs(peters_r - el.second.second);
                    if (ryad < el.second.second) {
                        ryad = el.second.second;
                        number = el.first;
                    }

                } else {
                    pre_ans = std::abs(peters_r - el.second.second);
                    ryad = el.second.second;
                    number = el.first;
                }
            }
        }
    }
    if (pre_ans == INT_MAX) {
        std::cout << -1;
        return 0;
    }
    std::cout << ryad + 1 << ' ' << (number % 2 == 0 ? 2 : 1);
    return 0;
}