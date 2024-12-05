#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <random>

struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;
    int val;
    long long sum; // хранит сумму на своем отрезке
    Node(int key) : key(key), priority(rand()), left(nullptr), right(nullptr), val(key), sum(key) {}
};
class Treap {
    Node* root_ = nullptr;

public:
    Node* merge(Node* l, Node* r) {
        if (!l) {
            return r;
        }
        if (!r) {
            return l;
        }
        if (l->priority > r->priority) {
            l->right = merge(l->right, r);
            update(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            update(r);
            return r;
        }
    }

    std::pair<Node*, Node*> split(Node* root, int x) {
        if (!root) {
            return {nullptr, nullptr};
        }
        if (root->key <= x) {
            auto [l, r] = split(root->right, x);
            root->right = l;
            update(root);
            return {root, r};
        } else {
            auto [l, r] = split(root->left, x);
            root->left = r;
            update(root);
            return {l, root};
        }
    }

    void insert(int x) {
        auto [l, r] = split(root_, x);
        Node* t = new Node(x);
        root_ = merge(merge(l, t), r);
    }

    static long long sum(Node* vertex) {
        return vertex ? vertex->sum : 0;
    }

    long long sum(int l, int r) {
        auto [l1, r1] = split(root_, r);
        auto [l2, r2] = split(l1, l - 1);
        long long segment_sum = sum(r2);
        root_ = merge(merge(l2, r2), r1);
        return segment_sum;
    }

    static void update(Node* vertex) {
        vertex->sum = sum(vertex->left) + sum(vertex->right) + vertex->val;
    }

    void buildTree(std::vector<int>& tree) {
        for (const auto& i : tree) {
            insert(i);
        }
    }

    void swapAllPairs(int l, int r) {
        for (int i = l - 1; i < r; i += 2) {
            auto [l1, r1] = split(root_, i);
            auto [l2, r2] = split(r1, i + 1);
            root_ = merge(merge(l2, l1), r2);
        }
    }

    void print(Node* node) {
        if (node) {
            print(node->left);
            std::cout << node->key << " ";
            print(node->right);
        }
    }

    void print() {
        print(root_);
        std::cout << std::endl;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Treap odd_tree;
    Treap even_tree;
    for (int i = 0; i < n; i++) {
        int el;
        std::cin >> el;
        if (i % 2 == 0) {
            even_tree.insert(el);
        } else {
            odd_tree.insert(el);
        }
    }
    int type, left, right;
    std::cout << "Swapper 1:\n";
    odd_tree.print();
    even_tree.print();
    for (int i = 0; i < m; i++) {
        std::cin >> type >> left >> right;
        if (type == 1) {
            treap.swapAllPairs(left, right);
        } else {
            std::cout << treap.sum(left, right) << '\n';
        }
    }
    return 0;
}

/*
1) 1 2 3 4 5
2) 1 3 2 5 4
3) return sum(l, r) = 10
4) 3 1 5 2 4
5) return sum(l, r) = 9
6) return sum(l, r) = 2
*/