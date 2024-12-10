#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int depth;
    TreeNode(int val, int depth) : val(val), left(nullptr), right(nullptr), depth(depth) {}
};

TreeNode* insert(TreeNode* root, int val, int depth = 1) {
    if (!root) {
        return new TreeNode(val, depth);
    }
    if (val == root->val) {
        return root;
    }
    if (val < root->val) {
        root->left = insert(root->left, val, depth + 1);
    } else {
        root->right = insert(root->right, val, depth + 1);
    }
    return root;
}

TreeNode* find(TreeNode* root, int val) {
    if (!root) {
        return nullptr;
    }
    if (val == root->val) {
        return root;
    }
    if (val < root->val) {
        return find(root->left, val);
    } else {
        return find(root->right, val);
    }
}

int main() {
    int vertex;
    TreeNode* root = nullptr;
    while (std::cin >> vertex) {
        if (!vertex) {
            break;
        }
        if (find(root, vertex)) {
            continue;
        }
        root = insert(root, vertex);
        std::cout << find(root, vertex)->depth << ' ';
    }
    return 0;
}