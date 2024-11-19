#include <iostream>
#include <vector>

int count_cycles(const std::vector<int>& paths) {
    int n = paths.size();
    std::vector<int> visited(n, 0);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            int current = i;
            while (visited[current] == 0) {
                visited[current] = i + 1;
                current = paths[current];
            }
            if (visited[current] == i + 1) {
                ++cnt;
            }
        }
    }
    return cnt;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> paths(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> paths[i];
        --paths[i];
    }
    std::cout << count_cycles(paths);
    return 0;
}