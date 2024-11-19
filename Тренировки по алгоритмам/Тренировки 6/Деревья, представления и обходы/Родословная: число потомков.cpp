#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

std::map<std::string, int> answer;

int dfs(const std::string& main_person, std::unordered_map<std::string, std::vector<std::string>>& tree) {
    int cnt = 0;
    if (tree.find(main_person) != tree.end()) {
        for (const auto& child : tree[main_person]) {
            cnt += 1 + dfs(child, tree);
        }
    }
    answer[main_person] = cnt;
    return cnt;
}

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<std::string, std::vector<std::string>> tree;
    std::unordered_set<std::string> children;
    for (int i = 0; i < n - 1; i++) {
        std::string child, parent;
        std::cin >> child >> parent;
        tree[parent].push_back(child);
        children.insert(child);
    }
    std::string main_person;
    for (const auto& [parent, child] : tree) {
        if (children.find(parent) == children.end()) {
            main_person = parent;
            break;
        }
    }
    dfs(main_person, tree);
    for (const auto& [k, v] : answer) {
        std::cout << k << ' ' << v << '\n';
    }
    return 0;
}