#include <iostream>
#include <string>
#include <climits>
#include <vector>

std::vector<long long> segment_tree;
std::vector<int> tree;

void buildTree(int vertex_number, int l, int r) {
    if (l == r) {
        segment_tree[vertex_number] = tree[l];
    } else {
        int mid = (l + r) / 2;
        buildTree(vertex_number * 2, l, mid);
        buildTree(vertex_number * 2 + 1, mid + 1, r);
        segment_tree[vertex_number] = segment_tree[vertex_number * 2] + segment_tree[vertex_number * 2 + 1];
    }
}

int getSum(int l, int r, int vertex_number, int l_bound, int r_bound) {
    if (l <= l_bound && r >= r_bound) {
        return segment_tree[vertex_number];
    }
    if (r_bound < l || r < l_bound)  {
        return 0;
    }
    int mid = (l_bound + r_bound) / 2;
    return getSum(l, r, vertex_number * 2, l_bound, mid)
    + getSum(l, r, vertex_number * 2 + 1, mid + 1, r_bound);
}

void swapModify(int l, int r, int vertex_number, int l_bound, int r_bound) {

}

int main() {
    int n, m;
    std::cin >> n >> m;
    segment_tree.assign(4 * n, 0);
    tree.assign(n, 0);
    for (int i = 0; i < n; i++) {
        int el;
        std::cin >> el;
        tree[i] = el;
    }
    buildTree(1, 0, n - 1);
    int type, left, right;
    std::cout << "Swapper 1:\n";
    for (int i = 0; i < m; i++) {
        std::cin >> type >> left >> right;
        if (type == 1) {
            continue;
        } else {
            std::cout << getSum(left - 1, right - 1, 1, 0, n - 1) << '\n';
        }
    }
    return 0;
}