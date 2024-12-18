#include <iostream>
#include <cmath>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::unordered_map<std::string, std::vector<std::string>> tree;
std::map<std::string, int> cnt;

void dfs(const std::string& root, int depth = 0) {
    cnt[root] = depth;
    if (tree[root].empty()) {
        return;
    }
    for (const auto& child : tree.at(root)) {
       dfs(child, depth + 1);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::unordered_set<std::string> children;
    for (int i = 0; i < n - 1; i++) {
        std::string parent, child;
        std::cin >> child >> parent;
        tree[parent].push_back(child);
        children.insert(child);
        children.insert(parent);
        cnt[child] = 0;
        cnt[parent] = 0;
    }
    for (const auto& [parent, children_tree] : tree) {
        for (const auto& child : children_tree) {
            if (children.find(child) != children.end()) {
                children.erase(child);
            }
        }
    }
    std::string root = *children.begin();
    dfs(root);
    for (const auto& [name, child] : cnt) {
        std::cout << name << ' ' << child << '\n';
    }
    return 0;
}