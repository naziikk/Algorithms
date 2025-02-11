#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> reversed;
std::vector<int> components_distribution;
std::vector<int> order;
std::vector<int> visited;
int current_component = 1;

void dfs1(int vertex) {
    visited[vertex] = true;
    for (const auto& neighbour : graph[vertex]) {
        if (!visited[neighbour]) {
            dfs1(neighbour);
        }
    }
    order.push_back(vertex);
}

void dfs2(int vertex) {
    components_distribution[vertex] = current_component;
    for (const auto& neighbour : reversed[vertex]) {
        if (components_distribution[neighbour] == -1) {
            dfs2(neighbour);
        }
    }
}

void TransposeGraph(int n) {
    for (int i = 0; i < n; i++) {
        for (const auto& neighbour : graph[i]) {
            reversed[neighbour].push_back(i);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    graph.resize(n);
    visited.resize(n);
    reversed.resize(n);
    components_distribution.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int from, to;
        std::cin >> from >> to;
        from--;
        to--;
        graph[from].push_back(to);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    TransposeGraph(n);

    std::reverse(order.begin(), order.end());

    for (int i = 0; i < n; i++) {
        if (components_distribution[order[i]] == -1) {
            dfs2(order[i]);
            current_component++;
        }
    }
    std::cout << current_component - 1 << '\n';
    for (int i = 0; i < n; i++) {
        std::cout << components_distribution[i] << ' ';
    }
    return 0;
}