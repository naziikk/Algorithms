#include <iostream>
#include <vector>

std::vector<int> answer;

int dfs(int prev, int main_person, std::vector<std::vector<int>>& tree) {
    int cnt = 0;
    if (!tree[main_person].empty()) {
        for (const auto& child : tree[main_person]) {
            if (child != prev) {
                cnt += 1 + dfs(main_person, child, tree);
            }
        }
    }
    answer[main_person] = cnt;
    return cnt;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> tree(n);
    answer.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int parent, child;
        std::cin >> parent >> child;
        tree[parent - 1].push_back(child - 1);
        tree[child - 1].push_back(parent - 1);
    }
    dfs(0, 0, tree);
    for (int i = 0; i < n; i++) {
        std::cout << answer[i] + 1 << ' ';
    }
    return 0;
}