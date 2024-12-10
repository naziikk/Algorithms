#include <iostream>
#include <string>
#include <climits>

struct TreeNode {
    int val_;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int depth = 0;
    TreeNode(int val, int depth) : val_(val), depth(depth), left(nullptr), right(nullptr) {}
};

TreeNode* Insert(int val, TreeNode* root, int depth = 0) {
    if (!root) {
        root = new TreeNode(val, depth);
        return root;
    }
    if (root->val_ == val) {
        return root;
    }
    if (val < root->val_) {
        root->left = Insert(val, root->left, depth + 1);
    } else {
        root->right = Insert(val, root->right, depth + 1);
    }
    return root;
}

std::pair<bool, int> dfs(TreeNode* root) {
    if (!root) {
        return {true, 0};
    }
    auto left = dfs(root->left);
    auto right = dfs(root->right);
    bool balanced = left.first && right.first && std::abs(left.second - right.second) <= 1;
    int height = std::max(left.second, right.second) + 1;
    return {balanced, height};
}

int main() {
    TreeNode* root = nullptr;
    int vertex = -1;
    while (std::cin >> vertex && vertex != 0) {
        root = Insert(vertex, root);
    }
    if (dfs(root).first) {
        std::cout << "YES";
        return 0;
    }
    std::cout << "NO";
    return 0;
}