#include <cstdint>
#include "btree.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <queue>

Node::Node(int t) : t(t), isLeaf(true), parent(nullptr) {
    key.reserve(2 * t - 1);
    children.reserve(2 * t);
}

BTree::BTree(int t) : t_(t), root(nullptr), size_(0) {}

BTree::~BTree() = default;

bool find(Node* root, int key) {
    while (root) {
        size_t i = 0;
        while (i < root->key.size() && key > root->key[i]) {
            i++;
        }
        if (i < root->key.size() && key == root->key[i]) {
            return true;
        }
        if (root->isLeaf) {
            return false;
        }
        root = root->children[i];
    }
    return false;
}

void split(Node* parent, int index, Node* child, int t_) {
    if (!child) {
        return;
    }
    Node* new_child = new Node(child->t);
    new_child->isLeaf = child->isLeaf;
    new_child->key.assign(child->key.begin() + t_, child->key.end());
    child->key.resize(t_ - 1);
    if (!child->isLeaf) {
        new_child->children.assign(child->children.begin() + t_, child->children.end());
        child->children.resize(t_);
        for (Node* grandchild : new_child->children) {
            if (grandchild) {
                grandchild->parent = new_child;
            }
        }
    }
    parent->children.insert(parent->children.begin() + index + 1, new_child);
    parent->key.insert(parent->key.begin() + index, child->key[t_ - 1]);
    new_child->parent = parent;
}

void insertKey(Node*& root, int key, int t_, int& size_) {
    // если находимся в листе, найдем позицию куда вставить ключ
    if (root->isLeaf) {
        if (root->key.size() == 2 * t_ - 1) {
            Node* new_root = new Node(t_);
            new_root->isLeaf = false;
            new_root->children.push_back(root);
            root->parent = new_root;
            split(new_root, 0, root, t_);
            root = new_root;
            size_ += 1;
        }
        // нашли позицию
        auto it = std::lower_bound(root->key.begin(), root->key.end(), key);
        // собственно вставили
        root->key.insert(it, key);
    } else {
        size_t i = 0;
        while (i < root->key.size() && key > root->key[i]) {
            i++;
        }
        if (root->children[i]->key.size() == 2 * t_ - 1) {
            split(root, i, root->children[i], t_);
            if (key > root->key[i]) {
                i++;
            }
            size_++;
        }
        insertKey(root->children[i], key, t_, size_);
    }
}

void BTree::insert(int key) {
    if (!root) {
        root = new Node(t_);
        root->key.push_back(key);
        root->parent = nullptr;
        size_++;
        return;
    }
    if (find(root, key)) {
        return;
    }
    if (root->key.size() == 2 * t_ - 1) {
        Node* new_root = new Node(t_);
        new_root->isLeaf = false;
        new_root->children.push_back(root);
        root->parent = new_root;
        split(new_root, 0, root, t_);
        root = new_root;
        size_ += 2;
    }
    insertKey(root, key, t_, size_);
}

size_t BTree::size() const {
    return size_;
}

int64_t BTree::sum() const {
    if (!root) {
        return 0;
    }
    int64_t sum = 0;
    std::function<void(Node*)> traverse = [&](Node* node) {
        if (node->isLeaf) {
            for (const auto& key : node->key) {
                sum += (long long) key;
            }
        } else {
            for (Node* child : node->children) {
                if (child) {
                    traverse(child);
                }
            }
        }
    };
    traverse(root);
    return sum;
}