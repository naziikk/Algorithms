#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::deque<int> l;
    std::deque<int> r;
    for (int i = 0; i < n; i++) {
        char action;
        int idx;
        std::cin >> action;
        if (action == '+') {
            std::cin >> idx;
            r.push_back(idx);
        }
        else if (action == '*') {
            std::cin >> idx;
            r.push_front(idx);
        }
        else {
            std::cout << l.front() << '\n';
            l.pop_front();
        }
        if (l.size() < r.size()) {
            l.push_back(r.front());
            r.pop_front();
        }
    }

    return 0;
}
