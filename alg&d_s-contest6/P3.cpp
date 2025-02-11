#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class DSU {
    std::vector<int> parent;
    std::vector<int> rank;

public:
    explicit DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int Find(int vertex) {
        if (vertex == parent[vertex]) {
            return vertex;
        }
        return parent[vertex] = Find(parent[vertex]);
    }

    void Unite(int vertex_a, int vertex_b) {
        int root_a = Find(vertex_a);
        int root_b = Find(vertex_b);
        if (root_a == root_b) {
            return;
        }
        if (rank[root_a] < rank[root_b]) {
            std::swap(root_a, root_b);
        }
        parent[root_b] = root_a;
        if (rank[root_a] == rank[root_b]) {
            rank[root_a]++;
        }
    }
};

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        std::cin >> edges[i].first >> edges[i].second;
    }

    std::set<std::pair<int, int>> cut_set;
    std::vector<std::pair<std::string, std::pair<int, int>>> queries(k);

    for (int i = 0; i < k; i++) {
        std::string type;
        int from, to;
        std::cin >> type >> from >> to;
        queries[i] = {type, {from, to}};
        if (type == "cut") {
            cut_set.insert({from, to});
        }
    }
    DSU dsu(n + 1);
    for (int i = 0; i < m; i++) {
        if (!cut_set.count({edges[i].first, edges[i].second})
            && !cut_set.count({edges[i].second, edges[i].first})) {
            std::cout << "hui" << ' ' << i << '\n';
            dsu.Unite(edges[i].first, edges[i].second);
        }
    }

    std::vector<std::string> ans;
    for (int i = k - 1; i >= 0; i--) {
        if (queries[i].first == "ask") {
            ans.push_back(dsu.Find(queries[i].second.first) == dsu.Find(queries[i].second.second) ? "YES" : "NO");
        } else {
            dsu.Unite(queries[i].second.first, queries[i].second.second);
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        std::cout << ans[i] << '\n';
    }
    return 0;
}