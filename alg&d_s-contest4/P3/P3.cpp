#include "avl_tree.h"

struct Node {
    int val_;
    Node* left = nullptr;
    Node* right = nullptr;
    int height;
};

Node::Node(int value) : val_(value), left(nullptr), right(nullptr), height(1) {}

Node::~Node() {}

AVLTree::AVLTree() {}

AVLTree::AVLTree(int value) {}

int AVLTree::getHeight() {
    if (!root) {
        return 0;
    }
}

void AVLTree::insert(int value) {}

void AVLTree::erase(int value) {}

int *AVLTree::find(int value) {}

int *AVLTree::traversal() {}

int *AVLTree::lowerBound(int value) {}

bool AVLTree::empty() {
    return
}

Node *AVLTree::getRoot() {}

int AVLTree::getSize() {}

AVLTree::~AVLTree() {}

int AVLTree::getNodeHeight(Node *node) {}

int AVLTree::balanceFactor(Node *node) {}

void AVLTree::balanceHeight(Node *node) {}

Node *AVLTree::rotateRight(Node *node) {}

Node *AVLTree::rotateLeft(Node *node) {}

Node *AVLTree::balanceNode(Node *node) {}

Node *AVLTree::insertNode(Node *node, int value) {}

Node *AVLTree::findMinNode(Node *node) {}

Node *AVLTree::removeMinNode(Node *node) {}

Node *AVLTree::removeNode(Node *node, int value) {}

Node *AVLTree::findNode(Node *node, int value) {}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {}