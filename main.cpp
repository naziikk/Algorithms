#include <cstdint>
#include "/Users/nazarzakrevskij/CLionProjects/AlgoAndDS_hw1/alg&d_s-contest4/btree.h"
#include <functional>
#include <algorithm>
#include <iostream>

#include <iomanip>

#include <queue>

void printTreeByLevels(Node* root) {
    if (!root) {
        return;
    }

    std::queue<Node*> q; // Очередь для BFS
    q.push(root);

    while (!q.empty()) {
        size_t levelSize = q.size(); // Количество узлов на текущем уровне

        // Обрабатываем все узлы текущего уровня
        for (size_t i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            // Выводим ключи текущего узла
            std::cout << "[ ";
            for (int key : current->key) {
                std::cout << key << " ";
            }
            std::cout << "] ";

            // Добавляем детей текущего узла в очередь
            for (Node* child : current->children) {
                if (child) {
                    q.push(child);
                }
            }
        }
        std::cout << "\n"; // Переход на следующий уровень
    }
}



Node::Node(int t) : t(t), isLeaf(true), parent(nullptr) {
    key.reserve(2 * t - 1);
    children.reserve(2 * t);
}

BTree::BTree(int t) : t_(t), root(nullptr), size_(0) {}

BTree::~BTree() = default;

bool find(Node* root, int key) {
    while (root) {
        for (size_t i = 0; i < root->key.size(); i++) {
            // если ключ меньше - пойдем в i-го ребенка
            if (key < root->key[i]) {
                if (root->children.empty()) {
                    return false;
                }
                root = root->children[i];
                break;
                // если нашли ключ - вернем true
            } else if (key == root->key[i]) {
                return true;
                // если это последний ключ - пойдем в следующего ребенка
            } else if (i == root->key.size() - 1) {
                if (root->children.empty()) {
                    return false;
                }
                root = root->children[i + 1];
            }
        }
        // если в листе - выйдем из цикла
        if (root->children.empty()) {
            return false;
        }
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
            size_++;
        }
        auto it = std::lower_bound(root->key.begin(), root->key.end(), key);
        root->key.insert(it, key);
    } else {
        for (size_t i = 0; i < root->key.size(); i++) {
            // попробуем вставить в текущий узел
            // если ключ меньше - пойдем в i-го ребенка
            if (key < root->key[i]) {
                if (root->children[i]) {
                    insertKey(root->children[i], key, t_, size_);
                    return;
                }
                return;
                // если это последний ключ - пойдем в последнего ребенка
            } else if (i == root->key.size() - 1 && i + 1 < root->children.size()) {
                insertKey(root->children[i + 1], key, t_, size_);
                return;
            }

        }
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
        size_++;
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
        for (const auto& key : node->key) {
            sum += key;
        }
        for (Node* child : node->children) {
            if (child) {
                traverse(child);
            }
        }
    };
    traverse(root);
    return sum;
}

int main() {
    BTree tree(3);

    std::cout << "Inserting 10:\n";
    tree.insert(10);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 20:\n";
    tree.insert(20);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 5:\n";
    tree.insert(5);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 6:\n";
    tree.insert(6);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 12:\n";
    tree.insert(12);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 30:\n";
    tree.insert(30);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 14:\n";
    tree.insert(14);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 14:\n";
    tree.insert(8);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 7:\n";
    tree.insert(7);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 13:\n";
    tree.insert(13);
    printTreeByLevels(tree.root);

    std::cout << "\nInserting 18:\n";
    tree.insert(18);
    printTreeByLevels(tree.root);

    std::cout << "\nSum of all keys: " << tree.sum() << std::endl;
    std::cout << "Tree size: " << tree.size() << std::endl;
}

