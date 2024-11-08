#include <iostream>
#include <unordered_map>
#include <queue>
#include <tuple>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* CreateTree(int n, std::unordered_map<int, std::tuple<TreeNode*, TreeNode*, bool>>& parent) {
    std::queue<TreeNode*> q;
    auto* root = new TreeNode(1);
    n--;
    q.push(root);
    parent[root->val] = {root, nullptr, true};
    while (n-- > 0) {
        TreeNode* node = q.front();
        q.pop();
        node->left = new TreeNode(node->val * 2);
        parent[node->left->val] = {node->left, node, true};
        q.push(node->left);
        n--;
        if (n >= 0) {
            node->right = new TreeNode(node->val * 2 + 1);
            q.push(node->right);
            parent[node->right->val] = {node->right, node, false};
        }
    }
    return root;
}

void PrintTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    PrintTree(root->left);
    std::cout << root->val << " ";
    PrintTree(root->right);
}

int main() {
    int n, q;
    std::cin >> n >> q;
    std::unordered_map<int, std::tuple<TreeNode*, TreeNode*, bool>> parent;
    TreeNode* root = CreateTree(n, parent);
    for (int i = 0; i < q; i++) {
        int x;
        std::cin >> x;
        auto [node, par, is_left] = parent[x];
        if (par == nullptr) {
            continue;
        }
        auto [node1, grandparent, is_left_grandparent] = parent[par->val];
        if (grandparent != nullptr && parent.find(grandparent->val) != parent.end()) {
            if (is_left_grandparent) {
                grandparent->left = nullptr;
                grandparent->left = node;
            } else {
                grandparent->right = nullptr;
                grandparent->right = node;
            }
            parent[x] = {node, grandparent, is_left_grandparent};
            if (is_left) {
                par->left = nullptr;
                par->left = node->left;
                if (node->left) {
                    parent[node->left->val] = {node->left, par, true};
                }
                node->left = par;
                parent[par->val] = {par, node, true};
            } else {
                par->right = nullptr;
                par->right = node->right;
                 if (node->right) {
                    parent[node->right->val] = {node->right, par, false};
                }
                node->right = par;
                parent[par->val] = {par, node, false};
            }
        } else {
            if (is_left) {
                par->left = nullptr;
                par->left = node->left;
                if (node->left) {
                    parent[node->left->val] = {node->left, par, true};
                }
                node->left = par;
                parent[par->val] = {par, node, true};
                parent[x] = {node, nullptr, true};
            } else {
                par->right = nullptr;
                par->right = node->right;
                if (node->right) {
                    parent[node->right->val] = {node->right, par, false};
                }
                node->right = par;
                parent[par->val] = {par, node, false};
                parent[x] = {node, nullptr, false};
            }
            root = node;
        }
    }
    PrintTree(root);
    return 0;
}