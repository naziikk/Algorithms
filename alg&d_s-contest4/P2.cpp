#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>

struct TreeNode {
    int val_;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    char color;
    TreeNode(int val, char color) : val_(val), color(color), left(nullptr), right(nullptr) {}
};

struct Data {
    int key;
    std::string left_child;
    std::string right_child;
    char color;
};

// проверяю что дерево валидно как BST запуская dfs рекурсивно в оба поддерева
// понял что можно не делать отдельную функцию и тут же проверять
// пункт 4) Если вершина – красная, то ее родитель – черный.
bool validateRBT(long l, long r, TreeNode* root) {
    if (!root) {
        return true;
    }
    // проверка валидности bst
    if (root->val_ <= l || root->val_ >= r) {
        return false;
    }
    // проверка пункта 4)
    if (root->color == 'R' && ((root->left && root->left->color == 'R') ||
    (root->right && root->right->color == 'R'))) {
        return false;
    }
    return validateRBT(l, root->val_, root->left) && validateRBT(root->val_, r, root->right);
}

// проверяю пути на количество черных вершин
bool checkRootToLeafPaths(TreeNode* root, int current, int& fix_cnt) {
    if (!root) {
        if (fix_cnt == -1) {
            fix_cnt = current;
        } else if (fix_cnt != current) {
            return false;
        }
        return true;
    }
    if (root->color == 'B') {
        current++;
    }
    return checkRootToLeafPaths(root->left, current, fix_cnt) &&
    checkRootToLeafPaths(root->right, current, fix_cnt);
}

TreeNode* buildTree(const std::unordered_map<int, Data>& tree, int root_number) {
    if (tree.find(root_number) == tree.end()) {
        return nullptr;
    }
    const auto& node_data = tree.at(root_number);
    auto* root = new TreeNode(node_data.key, node_data.color);
    if (node_data.left_child != "null") {
        root->left = buildTree(tree, std::stoi(node_data.left_child));
    }
    if (node_data.right_child != "null") {
        root->right = buildTree(tree, std::stoi(node_data.right_child));
    }
    return root;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, root_number;
    std::cin >> n;
    if (n == 0) {
        std::cout << "NO\n";
        return 0;
    }
    std::cin >> root_number;
    std::unordered_map<int, Data> tree;
    for (int i = 0; i < n; ++i) {
        int number;
        Data node_data;
        std::cin >> number >> node_data.key >> node_data.left_child >> node_data.right_child >> node_data.color;
        tree[number] = node_data;
    }
    TreeNode* root = buildTree(tree, root_number);
    if (root->color == 'R') {
        std::cout << "NO\n";
        return 0;
    }
    int fix_cnt = -1;
    if (!validateRBT(LONG_MIN, LONG_MAX, root) || !checkRootToLeafPaths(root, 0, fix_cnt)) {
        std::cout << "NO\n";
        return 0;
    }
    std::cout << "YES\n";
    return 0;
}
