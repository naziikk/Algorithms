#include <iostream>
#include <vector>
#include <algorithm>

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

struct Edge {
    int from;
    int to;
    int weight;
    int index;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int buildMinimumSpanningTree(int n, std::vector<Edge>& edge_list, int skip_index = -1, int add = -1) {
    DSU dsu(n);
    int total_weight = 0;
    int edges_used = 0;

    if (add != -1) {
        const auto& edge = edge_list[add];
        if (dsu.Find(edge.from) != dsu.Find(edge.to)) {
            dsu.Unite(edge.from, edge.to);
            total_weight += edge.weight;
            edges_used++;
        }
    }

    for (int i = 0; i < edge_list.size(); i++) {
        if (i == skip_index) continue;
        const auto& edge = edge_list[i];
        if (dsu.Find(edge.from) != dsu.Find(edge.to)) {
            dsu.Unite(edge.from, edge.to);
            total_weight += edge.weight;
            edges_used++;
        }
    }
    return edges_used == n - 1 ? total_weight : INT_MAX;
}

class Solution {
public:
    std::vector<std::vector<int>> findCriticalAndPseudoCriticalEdges(int n, std::vector<std::vector<int>>& edges) {
        std::vector<Edge> edge_list;
        edge_list.reserve(edges.size());
        for (int i = 0; i < edges.size(); i++) {
            edge_list.push_back({edges[i][0], edges[i][1], edges[i][2], i});
        }
        std::sort(edge_list.begin(), edge_list.end());
        int mst_weight = buildMinimumSpanningTree(n, edge_list);
        std::vector<int> critical_edges;
        std::vector<int> pseudo_critical_edges;
        for (const auto& edge : edge_list) {
            int weight_without_edge = buildMinimumSpanningTree(n, edge_list, edge.index);
            if (weight_without_edge > mst_weight) {
                critical_edges.push_back(edge.index);
            } else {
                int weight_with_edge = buildMinimumSpanningTree(n, edge_list, -1, edge.index);
                if (weight_with_edge == mst_weight) {
                    pseudo_critical_edges.push_back(edge.index);
                }
            }
        }
        return {critical_edges, pseudo_critical_edges};
    }
};