#include <iostream>
#include <vector>

struct TreeNode {
    int val_;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int depth = 0;
    TreeNode(int val, int depth) : val_(val), depth(depth), left(nullptr), right(nullptr) {}
};

bool SearchNode(int val, TreeNode* root) {
    if (!root) {
        return false;
    }
    if (root->val_ == val) {
        return true;
    }
    if (val < root->val_) {
        return SearchNode(val, root->left);
    } else {
        return SearchNode(val, root->right);
    }
}

TreeNode* AddNode(int val, TreeNode* root, bool& flag, int depth = 0) {
    if (!root) {
        root = new TreeNode(val, depth);
        flag = true;
        return root;
    }
    if (root->val_ == val) {
        flag = false;
        return root;
    }
    if (val < root->val_) {
        root->left = AddNode(val, root->left, flag, depth + 1);
    } else {
        root->right = AddNode(val, root->right, flag, depth + 1);
    }
    return root;
}

void PrintTree(TreeNode* root) {
    if (!root) {
        return;
    }
    PrintTree(root->left);
    std::cout << std::string(root->depth, '.') << root->val_ << "\n";
    PrintTree(root->right);
}

int main() {
    std::string operation;
    TreeNode* root = nullptr;
    while (std::cin >> operation) {
        if (operation == "SEARCH") {
            int val;
            std::cin >> val;
            if (SearchNode(val, root)) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        } else if (operation == "ADD") {
            int val;
            std::cin >> val;
            bool flag = false;
            root = AddNode(val, root, flag);
            if (flag) {
                std::cout << "DONE\n";
            } else {
                std::cout << "ALREADY\n";
            }
        } else if (operation == "PRINTTREE") {
            PrintTree(root);
        }
    }
    return 0;
}