#include "/Users/nazarzakrevskij/CLionProjects/AlgoAndDS_hw1/alg&d_s-contest4/P4/rbtree.h"

Node::Node(int key) : key(key), height(1), size(1), left(nullptr),
right(nullptr), parent(nullptr), color(Color::BLACK) {}

RBTree::RBTree() {
    root = nullptr;
}

RBTree::RBTree(std::initializer_list<int> list) {
    for (auto i = list.begin(); i != list.end(); i++) {
        insert(*i);
    }
}

RBTree::~RBTree() = default;

void updateSize(Node* node) {
    if (!node) {
        return;
    }
    node->size = 1;
    if (node->left) {
        node->size += node->left->size;
    }
    if (node->right) {
        node->size += node->right->size;
    }
}

void rotateRight(Node* node, Node*& root_) {
    Node* left_child = node->left;
    node->left = left_child->right;
    if (left_child->right) {
        left_child->right->parent = node;
    }
    left_child->parent = node->parent;
    if (node->parent) {
        if (node->parent->left == node) {
            node->parent->left = left_child;
        } else {
            node->parent->right = left_child;
        }
    } else {
        root_ = left_child;
    }
    left_child->right = node;
    node->parent = left_child;
    updateSize(node);
    updateSize(left_child);
}

void rotateLeft(Node* node, Node*& root_) {
    Node* right_child = node->right;
    node->right = right_child->left;
    if (right_child->left) {
        right_child->left->parent = node;
    }
    right_child->parent = node->parent;
    if (node->parent) {
        if (node->parent->right == node) {
            node->parent->right = right_child;
        } else {
            node->parent->left = right_child;
        }
    } else {
        root_ = right_child;
    }
    right_child->left = node;
    node->parent = right_child;
    updateSize(node);
    updateSize(right_child);
}

void correctBalance(Node* new_node, Node*& root) {
    while (new_node->parent && new_node->parent->color == Color::RED) {
        Node* grandparent = new_node->parent->parent;
        if (new_node->parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle && uncle->color == Color::RED) {
                new_node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                new_node = grandparent;
            } else {
                if (new_node == new_node->parent->right) {
                    new_node = new_node->parent;
                    rotateLeft(new_node, root);
                }
                new_node->parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateRight(grandparent, root);
            }
        } else {
            Node* uncle = grandparent->left;
            if (uncle && uncle->color == Color::RED) {
                new_node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                new_node = grandparent;
            } else {
                if (new_node == new_node->parent->left) {
                    new_node = new_node->parent;
                    rotateRight(new_node, root);
                }
                new_node->parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateLeft(grandparent, root);
            }
        }
    }
    root->color = Color::BLACK;
}

void RBTree::insert(int key) {
    Node* new_node = new Node(key);
    new_node->color = Color::RED;
    if (find(key)) {
        return;
    }
    if (size() == 0) {
        root = new Node(key);
        root->color = Color::BLACK;
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
        }
    }
    new_node->parent = parent;
    if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    Node* temp = new_node;
    while (temp) {
        updateSize(temp);
        temp = temp->parent;
    }
    correctBalance(new_node, root);
}


int *RBTree::find(int key) {
    Node* current = root;
    while (current) {
        if (key > current->key) {
            current = current->right;
        } else if (key < current->key) {
            current = current->left;
        } else {
            return &current->key;
        }
    }
    return nullptr;
}

int RBTree::size() const {
    return root ? root->size : 0;
}

int *RBTree::lowerBound(int key) {
    Node* node = nullptr;
    Node* current = root;
    while (current) {
        if (current->key >= key) {
            node = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (!node) {
        return nullptr;
    }
    return &node->key;
}

bool RBTree::empty() const {
    return size() == 0;
}

int RBTree::height() const {
    return root ? root->height : 0;
}
