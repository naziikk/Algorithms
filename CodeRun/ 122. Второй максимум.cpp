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

int getSecondMax(TreeNode* root) {
    TreeNode* current = root;
    TreeNode* parent = nullptr;
    while (current->right) {
        parent = current;
        current = current->right;
    }
    if (current->left) {
        TreeNode* temp = current->left;
        while (temp->right) {
            temp = temp->right;
        }
        return temp->val;
    }
    return parent->val;
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
    std::cout << getSecondMax(root);
    return 0;
}