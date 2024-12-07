#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <random>

std::mt19937 rnd(time(nullptr));
std::uniform_int_distribution<int> dist(0, INT_MAX);

struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;
    int cnt; // хранит количество вершин в поддереве
    long long sum; // хранит сумму на своем отрезке
    Node(int key) : key(key), priority(rnd()), left(nullptr), right(nullptr), sum(key), cnt(0) {}
};

class Treap {
public:
    void merge(Node* l, Node* r, Node*& root) {
        if (!l || !r) {
            root = l ? l : r;
        } else if (l->priority > r->priority) {
            merge(l->right, r, l->right);
            root = l;
        } else {
            merge(l, r->left, r->left);
            root = r;
        }
        update(root);
    }

    void Split(Node* temp, Node*& left_tree, Node*& right_tree, int key) {
        if (!temp) {
            return void(left_tree = right_tree = 0 );
        }
        if (key <= SubtreeCount(temp->left)) {
            Split(temp->left, left_tree, temp->left, key);
            right_tree = temp;
        } else {
            Split(temp->right, temp->right, right_tree, key - SubtreeCount(temp->left) - 1);
            left_tree = temp;
        }
        update(temp);
    }

    static long long sum(Node* vertex) {
        return vertex ? vertex->sum : 0;
    }

    long long sum(int l, int r, Node*& even_tree, Node*& odd_tree) {
        if (l > r) {
            return 0;
        }
        int l1 = (l + 1) / 2;
        int r1 = r / 2;
        int l2 = l / 2;
        int r2 = (r + 1) / 2 - 1;
        Node *first_1 = nullptr, *second_1 = nullptr, *third_1 = nullptr;
        Node *first_2 = nullptr, *second_2 = nullptr, *third_2 = nullptr;
        Split(even_tree, first_1, second_1, l1);
        Split(second_1, second_1, third_1, r1 - l1 + 1);
        Split(odd_tree, first_2, second_2, l2);
        Split(second_2, second_2, third_2, r2 - l2 + 1);
        long long ans = sum(second_1) + sum(second_2);
        merge(first_1, second_1, second_1);
        merge(second_1, third_1, even_tree);
        merge(first_2, second_2, second_2);
        merge(second_2, third_2, odd_tree);
        return ans;
    }

    static void update(Node* vertex) {
        if (vertex) {
            vertex->cnt = 1 + SubtreeCount(vertex->left) + SubtreeCount(vertex->right);
            vertex->sum = sum(vertex->left) + sum(vertex->right) + vertex->key;
        }
    }

    void swapAllPairs(int l, int r, Node*& even_tree, Node*& odd_tree) {
        int l1 = (l + 1) / 2;
        int r1 = r / 2;
        int l2 = l / 2;
        int r2 = (r + 1) / 2 - 1;
        Node *first_1 = nullptr, *second_1 = nullptr, *third_1 = nullptr;
        Node *first_2 = nullptr, *second_2 = nullptr, *third_2 = nullptr;
        Split(even_tree, first_1, second_1, l1);
        Split(second_1, second_1, third_1, r1 - l1 + 1);
        Split(odd_tree, first_2, second_2, l2);
        Split(second_2, second_2, third_2, r2 - l2 + 1);

        merge(first_1, second_2, second_2);
        merge(second_2, third_1, even_tree);
        merge(first_2, second_1, second_1);
        merge(second_1, third_2, odd_tree);
    }

    static int SubtreeCount(Node*& t) {
        return t ? t->cnt : 0;
    }
};

int test_case = 1;
int main() {
    int n, m;
    while (true) {
        std::cin >> n >> m;
        if (n + m == 0) {
            break;
        }
        if (test_case != 1) {
            std::cout << '\n';
        }
        Node *even_tree = nullptr;
        Node *odd_tree = nullptr;
        Treap treap;
        for (int i = 0; i < n; i++) {
            int el;
            std::cin >> el;
            if (i % 2 == 0) {
                treap.merge(even_tree, new Node(el), even_tree);
            } else {
                treap.merge(odd_tree, new Node(el), odd_tree);
            }
        }
        std::cout << "Swapper " << test_case << ":\n";
        int type, left, right;
        for (int i = 0; i < m; i++) {
            std::cin >> type >> left >> right;
            left--;
            right--;
            if (type == 1) {
                treap.swapAllPairs(left, right, even_tree, odd_tree);
            } else {
                std::cout << treap.sum(left, right, even_tree, odd_tree) << '\n';
            }
        }
        test_case++;
    }
    return 0;
}
