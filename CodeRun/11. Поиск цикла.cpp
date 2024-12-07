#include <iostream>
#include <vector>
#include <climits>


int start = -1;
int end = -1;
std::vector<int> visited;
std::vector<int> parents;
std::vector<std::vector<int>> graph;

bool hasCycle(int vertex, int prev) {
    visited[vertex] = 1;
    for (const auto& neighbour : graph[vertex]) {
        if (neighbour == prev) {
            continue;
        }
        if (visited[neighbour] == 0) {
            parents[neighbour] = vertex;
            if (hasCycle(neighbour, vertex)) {
                return true;
            }
        } else if (visited[neighbour] == 1) {
            start = neighbour;
            end = vertex;
            return true;
        }
    }
    visited[vertex] = -1;
    return false;
}

int main() {
    int n;
    std::cin >> n;
    graph.resize(n);
    visited.assign(n, 0);
    parents.assign(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            std::cin >> w;
            if (w != 0) {
                graph[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (hasCycle(i, -1)) {
            break;
        }
    }
    if (start == -1) {
        std::cout << "NO";
    } else {
        std::vector<int> ans;
        ans.push_back(start);
        for (int v = end; v != start; v = parents[v]) {
            ans.push_back(v);
        }
        std::cout << "YES" << '\n';
        std::cout << ans.size() << '\n';
        for (int i = ans.size() - 1; i >= 0; i--) {
            std::cout << ans[i] + 1 << ' ';
        }
    }
    return 0;
}