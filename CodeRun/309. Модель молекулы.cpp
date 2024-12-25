#include <iostream>
#include <vector>

struct Path {
    int from;
    int to;
};

class DSU {
public:
    explicit DSU(int n) : parent(n + 1), rank(n + 1, 1), components(n) {
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int vertex) {
        if (parent[vertex] == vertex) {
            return vertex;
        } else {
            return parent[vertex] = find(parent[vertex]);
        }
    }

    bool unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x != root_y) {
            if (rank[root_x] < rank[root_y]) {
                std::swap(root_x, root_y);
            }
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y]) {
                rank[root_x]++;
            }
            components--;
            return true;
        }
        return false;
    }

    int getComponents() const {
        return components;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
    int components;
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Path> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].from >> edges[i].to;
    }
    int q;
    std::cin >> q;
    std::vector<int> to_remove(q);
    std::vector<bool> is_removed(m, false);
    for (int i = 0; i < q; ++i) {
        std::cin >> to_remove[i];
        to_remove[i]--;
        is_removed[to_remove[i]] = true;
    }
    DSU union_find(n);
    for (int i = 0; i < m; ++i) {
        if (!is_removed[i]) {
            union_find.unite(edges[i].from, edges[i].to);
        }
    }
    std::vector<int> ans(q);
    for (int i = q - 1; i >= 0; --i) {
        ans[i] = union_find.getComponents();
        union_find.unite(edges[to_remove[i]].from, edges[to_remove[i]].to);
    }
    for (int i = 0; i < q; ++i) {
        std::cout << ans[i] << " ";
    }
    return 0;
}