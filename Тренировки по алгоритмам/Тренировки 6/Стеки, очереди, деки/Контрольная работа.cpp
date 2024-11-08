#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

struct Rover {
    int direction;
    int arrival_time;
    int idx;
    int id;
};

bool isRightOf(int first, int second) {
    return (first == 1 && second == 4) || (first == 2 && second == 1) ||
           (first == 3 && second == 2) || (first == 4 && second == 3);
}

int main() {
    int n;
    std::cin >> n;
    int k = n;
    int main_a, main_b;
    std::cin >> main_a >> main_b;
    std::vector<Rover> rovers(n);
    for (int i = 0; i < n; i++) {
        std::cin >> rovers[i].direction >> rovers[i].arrival_time;
        rovers[i].idx = i;
    }
    std::sort(rovers.begin(), rovers.end(), [main_a, main_b](const Rover& first, const Rover& second) {
        if (first.arrival_time != second.arrival_time) {
            return first.arrival_time < second.arrival_time;
        }
        bool first_main = (first.direction == main_a || first.direction == main_b);
        bool second_main = (second.direction == main_a || second.direction == main_b);

        if (first_main != second_main) {
            return first_main > second_main;
        }
        if (first_main == second_main) {
            return isRightOf(second.direction, first.direction);
        }
        return first.idx < second.idx;
    });
    for (int i = 0; i < n; i++) {
        rovers[i].id = i;
    }
    std::vector<int> ans(n);
    while (n != 0) {
        ans[rovers[0].idx] = rovers[0].arrival_time;
        std::vector<Rover> new_rovers;
        std::unordered_map<int, int> mp;
        for (int i = 1; i < rovers.size(); i++) {
            if (rovers[i].arrival_time <= rovers[0].arrival_time) {
                if ((rovers[0].direction == main_a || rovers[0].direction == main_b) &&
                    (rovers[i].direction == main_a || rovers[i].direction == main_b)) {
                    if ((rovers[0].direction == 1 && rovers[i].direction == 3)
                    || (rovers[0].direction == 3 && rovers[i].direction == 1)
                    || (rovers[0].direction == 2 && rovers[i].direction == 4)
                    || (rovers[0].direction == 4 && rovers[i].direction == 2)) {
                        rovers[i].arrival_time = std::max(mp[rovers[i].direction] + 1, rovers[i].arrival_time);
                        mp[rovers[i].direction] = std::max(mp[rovers[i].direction], rovers[i].arrival_time);
                        new_rovers.push_back(rovers[i]);
                    } else {
                        rovers[i].arrival_time = std::max(mp[rovers[i].direction] + 1, rovers[i].arrival_time + 1);
                        mp[rovers[i].direction] = std::max(mp[rovers[i].direction], rovers[i].arrival_time);
                        new_rovers.push_back(rovers[i]);
                    }
                } else if ((rovers[0].direction != main_a && rovers[0].direction != main_b) &&
                    (rovers[i].direction != main_a && rovers[i].direction != main_b)) {
                    if ((rovers[0].direction == 1 && rovers[i].direction == 3)
                    || (rovers[0].direction == 3 && rovers[i].direction == 1)
                    || (rovers[0].direction == 2 && rovers[i].direction == 4)
                    || (rovers[0].direction == 4 && rovers[i].direction == 2)) {
                        rovers[i].arrival_time = std::max(mp[rovers[i].direction] + 1, rovers[i].arrival_time);
                        mp[rovers[i].direction] = std::max(mp[rovers[i].direction], rovers[i].arrival_time);
                        new_rovers.push_back(rovers[i]);
                    } else {
                        rovers[i].arrival_time = std::max(mp[rovers[i].direction] + 1, rovers[i].arrival_time + 1);
                        mp[rovers[i].direction] = std::max(mp[rovers[i].direction], rovers[i].arrival_time);
                        new_rovers.push_back(rovers[i]);
                    }
                } else {
                    rovers[i].arrival_time = std::max(mp[rovers[i].direction] + 1, rovers[i].arrival_time + 1);
                    mp[rovers[i].direction] = std::max(mp[rovers[i].direction], rovers[i].arrival_time);
                    new_rovers.push_back(rovers[i]);
                }
            } else {
                rovers[i].arrival_time = std::max(mp[rovers[i].direction] + 1, rovers[i].arrival_time);
                mp[rovers[i].direction] = std::max(mp[rovers[i].direction], rovers[i].arrival_time);
                new_rovers.push_back(rovers[i]);
            }
        }
        rovers = new_rovers;
        std::sort(rovers.begin(), rovers.end(), [main_a, main_b](const Rover& first, const Rover& second) {
            if (first.arrival_time != second.arrival_time) {
                return first.arrival_time < second.arrival_time;
            }
            bool first_main = (first.direction == main_a || first.direction == main_b);
            bool second_main = (second.direction == main_a || second.direction == main_b);

            if (first_main != second_main) {
                return first_main > second_main;
            }
            if (first_main == second_main) {
                return isRightOf(second.direction, first.direction);
            }
            return first.id < second.id;
        });
        n--;
    }
    for (int i = 0; i < k; i++) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}