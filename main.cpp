#include <iostream>
#include <vector>

class DSU {
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DSU(int n) {
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

    bool Union(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);
        if (root_x == root_y) {
            return false;
        }
        if (rank[root_x] < rank[root_y]) {
            std::swap(root_x, root_y);
        }
        parent[root_y] = root_x;
        if (rank[root_x] == rank[root_y]) {
            rank[root_x]++;
        }
        return true;
    }
};

class Solution {
public:
    std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>>& edges) {
        int n = edges.size();
        DSU dsu(n + 1);
        std::vector<int> parent(n + 1, -1);
        int first_candidate = -1;
        int second_candidate = -1;
        for (int i = 0; i < n; i++) {
            int from = edges[i][0];
            int to = edges[i][1];
            if (parent[to] != -1) {
                first_candidate = parent[to];
                second_candidate = i;
                break;
            }
            parent[to] = i;
        }
        for (int i = 0; i < n; i++) {
            if (i == second_candidate) {
                continue;
            }
            if (!dsu.Union(edges[i][0], edges[i][1])) {
                if (first_candidate == -1) {
                    return edges[i];
                }
                return edges[first_candidate];
            }
        }
        return edges[second_candidate];
    }
};