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

void inOrderTraversal(TreeNode* root) {
    if (!root) {
        return;
    }
    inOrderTraversal(root->left);
    std::cout << root->val << '\n';
    inOrderTraversal(root->right);
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
    inOrderTraversal(root);
    return 0;
}