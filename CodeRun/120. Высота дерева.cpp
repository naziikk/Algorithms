#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int val) {
    if (!root) {
        return new TreeNode(val);
    }
    if (val == root->val) {
        return root;
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

int depth(TreeNode* root) {
    if (!root) {
        return 0;
    }
    int left = depth(root->left);
    int right = depth(root->right);
    return std::max(left, right) + 1;
}

int main() {
    int vertex;
    TreeNode* root = nullptr;
    while (std::cin >> vertex) {
        if (!vertex) {
            break;
        }
        root = insert(root, vertex);
    }
    std::cout << depth(root);
    return 0;
}