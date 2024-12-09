#include "/Users/nazarzakrevskij/CLionProjects/AlgoAndDS_hw1/alg&d_s-contest4/P7/splay-tree.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Node::Node(int key, Node *parent) : key(key), parent(parent), left(nullptr), right(nullptr) {}

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree() = default;

void SplayTree::insert(int key) {
    if (!root) {
        root = new Node(key, nullptr);
        return;
    }
    Node* node = find(key);
    if (node) {
        return;
    }
    Node* current = root;
    Node* parent = nullptr;
    while (current) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            return;
        }
    }
    Node* new_node = new Node(key, parent);
    if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

Node *SplayTree::find(int key) const {
    Node* current = root;
    while (current) {
        if (current->key < key) {
            current = current->right;
        } else if (current->key > key) {
            current = current->left;
        } else {
            return current;
        }
    }
    return nullptr;
}

int SplayTree::splay(Node* node) {
    if (!node) {
        return 0;
    }
    int cnt = 0;
    while (node->parent) {
        // если у узла нет дедушки, то выполняем один поворот, чтобы сделать node корнем.
        if (!node->parent->parent) {
            // если node — левый потомок, выполняем правый поворот.
            if (node->parent->left == node) {
                rotateRight(node->parent);
            } else { // иначе левый поворот
                rotateLeft(node->parent);
            }
            cnt++;
            // если node и его родитель оба левые потомки (zig-zig).
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
            rotateRight(node->parent->parent); // поворот вокруг дедушки.
            rotateRight(node->parent);        // поворот вокруг отца.
            cnt += 2;
            // если node и его родитель оба правые потомки (zig-zig).
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
            rotateLeft(node->parent->parent); // поворот вокруг дедушки.
            rotateLeft(node->parent);        // поворот вокруг отца.
            cnt += 2;
            // если node — левый потомок, а его родитель — правый (zig-zag случай).
        } else if (node->parent->left == node && node->parent->parent->right == node->parent) {
            rotateRight(node->parent);         // поворот вокруг дедушки.
            rotateLeft(node->parent);         // поворот вокруг отца.
            cnt++;
            // если node — правый потомок, а его родитель — левый (zig-zag случай).
        } else if (node->parent->right == node && node->parent->parent->left == node->parent) {
            rotateLeft(node->parent);
            rotateRight(node->parent);
            cnt++;
        }
    }
    // после завершения всех операций node становится корнем дерева.
    root = node;
    return cnt;
}

int SplayTree::getHeight() const {
    return getHeight(root) - 1;
}

void SplayTree::clear(Node* node) {
    if (!node) {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}


void SplayTree::rotateLeft(Node *node) {
    Node* right_node = node->right;
    node->right = right_node->left;
    if (right_node->left) {
        right_node->left->parent = node;
    }
    right_node->parent = node->parent;
    if (node->parent) {
        if (node->parent->right == node) {
            node->parent->right = right_node;
        } else {
            node->parent->left = right_node;
        }
    } else {
        root = right_node;
    }
    right_node->left = node;
    node->parent = right_node;
}

void SplayTree::rotateRight(Node *node) {
    Node* left_node = node->left;
    node->left = left_node->right;
    if (left_node->right) {
        left_node->right->parent = node;
    }
    left_node->parent = node->parent;
    if (node->parent) {
        if (node->parent->left == node) {
            node->parent->left = left_node;
        } else {
            node->parent->right = left_node;
        }
    } else {
        root = left_node;
    }
    left_node->right = node;
    node->parent = left_node;
}

int SplayTree::getHeight(Node *node) const {
    if (!node) {
        return 0;
    }
    int left_height = getHeight(node->left);
    int right_height = getHeight(node->right);
    return 1 + std::max(left_height, right_height);
}