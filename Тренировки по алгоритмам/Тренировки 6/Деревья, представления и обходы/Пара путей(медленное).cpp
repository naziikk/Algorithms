#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int mod = 1e9 + 7;

std::pair<int, int> dfs(int n, std::vector<std::vector<int>>& tree, int start) {
    std::queue<int> vertexes;
    std::vector<int> dist(n + 1, -1);
    vertexes.push(start);
    dist[start] = 0;
    int farthest = start;
    int maxi = 0;
    while (!vertexes.empty()) {
        auto vertex = vertexes.front();
        vertexes.pop();
        for (auto adj : tree[vertex]) {
            if (dist[adj] == -1) {
                dist[adj] = dist[vertex] + 1;
                vertexes.push(adj);
                if (dist[adj] > maxi) {
                    maxi = dist[adj];
                    farthest = adj;
                }
            }
        }
    }
    return {farthest, maxi};
}

int findDiametr(std::vector<std::vector<int>>& tree, int n, int vertex) {
    auto [u, _] = dfs(n, tree, vertex);
    auto [_1, diametr] = dfs(n, tree, u);
    return diametr;
}

void addEdge(std::vector<std::vector<int>>& tree, int from, int to) {
    tree[from].push_back(to);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> tree(n + 1);
    for (int i = 1; i < n; i++) {
        int from, to;
        std::cin >> from >> to;
        addEdge(tree, from, to);
        addEdge(tree, to, from);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (const auto& node : tree[i]) {
            std::vector<std::vector<int>> cloned_tree = tree;
            cloned_tree[i].erase(std::find(cloned_tree[i].begin(), cloned_tree[i].end(), node));
            cloned_tree[node].erase(std::find(cloned_tree[node].begin(), cloned_tree[node].end(), i));
            long long first_diametr = findDiametr(cloned_tree, n, i);
            long long second_diametr = findDiametr(cloned_tree, n, node);
            ans = std::max(ans, first_diametr * second_diametr);
        }
    }
    std::cout << ans;
    return 0;
}