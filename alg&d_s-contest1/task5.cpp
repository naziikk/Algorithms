#include <iostream>
#include <list>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::list<int> queue;
    for (int i = 0; i < n; ++i) {
        char action;
        std::cin >> action;
        if (action == '+') {
            int idx;
            std::cin >> idx;
            queue.push_back(idx);
        }
        else if (action == '*') {
            int idx;
            std::cin >> idx;
            int mid = queue.size() / 2;
            if (queue.size() % 2 != 0) {
                ++mid;
            }
            auto it = queue.begin();
            std::advance(it, mid);
            queue.insert(it, idx);
        }
        else if (action == '-') {
            std::cout << queue.front() << '\n';
            queue.pop_front();
        }
    }

    return 0;
}