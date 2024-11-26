#include <unordered_map>
#include <vector>

struct Node {
    char value;
    int mask;
    Node* left;
    Node* right;

    Node(char charValue, Node* leftNode = nullptr, Node* rightNode = nullptr)
        : value(charValue), mask(1 << charValue), left(leftNode), right(rightNode) {}
};

class FindSubtrees {
    std::unordered_map<int, Node*> nodes;
    std::pair<int, Node*> bests[2] = {{0, nullptr}, {0, nullptr}};

public:
    std::pair<Node*, Node*> solve(Node* root) {
        dfs(root);
        return {bests[0].second, bests[1].second};
    }

    void dfs(Node* root) {
        if (root == nullptr) {
            return;
        }
        dfs(root->left);
        dfs(root->right);
        if (root->left != nullptr) {
            root->mask |= root->left->mask;
        }
        if (root->right != nullptr) {
            root->mask |= root->right->mask;
        }
        if (nodes.find(root->mask) == nodes.end()) {
            nodes[root->mask] = root;
        } else {
            if (root->mask >= bests[0].first) {
                bests[1] = bests[0];
                bests[0] = {root->mask, root};
            }
        }
    }
};

std::pair<Node*, Node*> getAns(Node* root) {
    FindSubtrees findSubtrees;
    return findSubtrees.solve(root);
}