#include "/Users/nazarzakrevskij/CLionProjects/AlgoAndDS_hw1/alg&d_s-contest4/P3/avl tree.h"
#include <queue>
#include <functional>
#include <climits>
#include <cmath>

Node::Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}

Node::~Node() {
    delete left;
    delete right;
}

AVLTree::AVLTree() : root_(nullptr), size_(0) {}

AVLTree::AVLTree(int value) {
    root_ = new Node(value);
}

int AVLTree::getHeight() {
    return getNodeHeight(root_);
}

void AVLTree::insert(int value) {
    if (!find(value)) {
        root_ = insertNode(root_, value);
        size_++;
    }
}

void AVLTree::erase(int value) {
    if (find(value)) {
        root_ = removeNode(root_, value);
        size_--;
    }
}

int *AVLTree::find(int value) {
    Node* found = findNode(root_, value);
    if (!found) {
        return nullptr;
    }
    return &found->value;
}

int *AVLTree::traversal() {
    int* ans = new int[size_];
    int index = 0;
    traversalInternal(root_, ans, &index);
    return ans;
}

int *AVLTree::lowerBound(int value) {
    Node* node = lowerBoundInternal(root_, value);
    if (!node) {
        return nullptr;
    }
    return &node->value;
}

bool AVLTree::empty() {
    return size_ == 0;
}

Node *AVLTree::getRoot() {
    return root_;
}

int AVLTree::getSize() {
    return size_;
}

AVLTree::~AVLTree() {
    delete root_;
}

int AVLTree::getNodeHeight(Node *node) {
    if (!node) {
        return 0;
    }
    return node->height;
}

int AVLTree::balanceFactor(Node *node) {
    if (!node) {
        return 0;
    }
    return getNodeHeight(node->left) - getNodeHeight(node->right);
}

void AVLTree::balanceHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    }
}

Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + std::max(getNodeHeight(y->left), getNodeHeight(y->right));
    x->height = 1 + std::max(getNodeHeight(x->left), getNodeHeight(x->right));
    return x;
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + std::max(getNodeHeight(x->left), getNodeHeight(x->right));
    y->height = 1 + std::max(getNodeHeight(y->left), getNodeHeight(y->right));
    return y;
}

Node* AVLTree::balanceNode(Node* node) {
    int balance = balanceFactor(node);
    if (balance > 1) {
        if (balanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if (balance < -1) {
        if (balanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}


Node *AVLTree::insertNode(Node *node, int value) {
    if (!node) {
        return new Node(value);
    }
    if (value == node->value) {
        return node;
    }
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else {
        node->right = insertNode(node->right, value);
    }
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    return balanceNode(node);
}

Node *AVLTree::findMinNode(Node *node) {
    if (!node) {
        return nullptr;
    }
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node *AVLTree::removeMinNode(Node *node) {
     if (!node->left) {
        Node* temp = node;
        node = node->right;
        delete temp;
        return node;
    }
    node->left = removeMinNode(node->left);
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    return balanceNode(node);
}

Node* AVLTree::removeNode(Node* node, int value) {
    if (!node) {
        return node;
    }
    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = findMinNode(node->right);
        node->value = temp->value;
        node->right = removeNode(node->right, temp->value);
    }
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    return balanceNode(node);
}

Node *AVLTree::findNode(Node *node, int value) {
    if (!node) {
        return nullptr;
    }
    if (value == node->value) {
        return node;
    }
    if (value < node->value) {
        return findNode(node->left, value);
    }
    return findNode(node->right, value);
}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {
    if (!node) {
        return;
    }
    traversalInternal(node->left, array, index);
    array[(*index)++] = node->value;
    traversalInternal(node->right, array, index);
}

Node* AVLTree::lowerBoundInternal(Node* current, int value) const {
    Node* result = nullptr;
    while (current) {
        if (current->value >= value) {
            result = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return result;
}
