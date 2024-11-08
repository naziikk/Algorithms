#include <iostream>
#include <set>

int main() {
    int n;
    std::cin >> n;
    std::set<std::pair<int, int>> st;
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        st.insert({x, y});
    }
    std::vector<std::pair<int, int>> ans(4);
    for (auto [first_x, first_y] : st) {
        for (auto [second_x, second_y] : st) {
            if (first_x == second_x && first_y == second_y) {
                continue;
            }
            int cnt = 2;
            std::vector<std::pair<int, int>> temp;
            int x_dif = abs(first_x - second_x);
            int y_dif = abs(first_y - second_y);
            if (first_x < second_x && first_y < second_y) {
                if (st.find({first_x + y_dif, first_y - x_dif}) != st.end()) {
                    cnt++;
                } else {
                    temp.emplace_back(first_x + y_dif, first_y - x_dif);
                }
                if (st.find({second_x + y_dif, second_y - x_dif}) != st.end()) {
                    cnt++;
                } else {
                    temp.emplace_back(second_x + y_dif, second_y - x_dif);
                }
                if (4 - cnt < ans.size()) {
                    ans = temp;
                }
                temp.clear();
                cnt = 2;
                if (st.find({first_x - y_dif, first_y + x_dif}) != st.end()) {
                    cnt++;
                } else {
                    temp.emplace_back(first_x - y_dif, first_y + x_dif);
                }
                if (st.find({second_x - y_dif, second_y + x_dif}) != st.end()) {
                    cnt++;
                } else {
                    temp.emplace_back(second_x - y_dif, second_y + x_dif);
                }
                if (4 - cnt < ans.size()) {
                    ans = temp;
                }
            } else {
                if (st.find({first_x - y_dif, first_y - x_dif}) != st.end()) {
                    cnt++;
                } else {
                    temp.emplace_back(first_x - y_dif, first_y - x_dif);
                }
                if (st.find({second_x - y_dif, second_y - x_dif}) != st.end()) {
                    cnt++;
                } else {
                    temp.emplace_back(second_x - y_dif, second_y - x_dif);
                }
                if (4 - cnt < ans.size()) {
                    ans = temp;
                }
                temp.clear();
                cnt = 2;
                if (st.find({first_x + y_dif, first_y + x_dif}) != st.end()) {
                    cnt++;
                } else {
                    temp.emplace_back(first_x + y_dif, first_y + x_dif);
                }
                if (st.find({second_x + y_dif, second_y + x_dif}) != st.end()) {
                    cnt++;
                } else {
                    temp.emplace_back(second_x + y_dif, second_y + x_dif);
                }
                if (4 - cnt < ans.size()) {
                    ans = temp;
                }
            }
        }
    }
    if (ans.size() == 4) {
        auto [x, y] = *st.begin();
        std::cout << 3 << '\n';
        std::cout << x + 1 << ' ' << y + 1 << '\n';
        std::cout << x + 1 << ' ' << y << '\n';
        std::cout << x << ' ' << y + 1 << '\n';
        return 0;
    }
    std::cout << ans.size() << '\n';
    for (auto el : ans) {
        std::cout << el.first << ' ' << el.second << '\n';
    }
    return 0;
}