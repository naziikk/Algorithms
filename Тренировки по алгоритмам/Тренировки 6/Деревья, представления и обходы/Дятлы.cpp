#include <iostream>
#include <vector>
#include <cmath>

bool hasCycle(const std::vector<std::vector<int>>& tree, int vertex, int prev, std::vector<int>& vis) {
    if (vis[vertex]) {
        return true;
    }
    vis[vertex] = 1;
    for (const auto& neighbour : tree[vertex]) {
        if (neighbour != prev) {
            if (hasCycle(tree, neighbour, vertex, vis)) {
                return true;
            }
        }
    }
    return false;
}

std::vector<long long> precomputeFactorials(int n, int k) {
    long long current_prod = 1;
    std::vector<long long> factorials(n + 1);
    factorials[0] = 1;
    for (long long i = 1; i <= n; i++) {
        current_prod = (current_prod % k) * (i % k) % k;
        factorials[i] = current_prod;
    }
    return factorials;
}

void dfs(int vertex, int current_component, const std::vector<std::vector<int>>& tree, std::vector<int>& components, std::vector<int>& new_component) {
    components[vertex] = current_component;
    new_component.push_back(vertex);
    for (const auto& neigbour : tree[vertex]) {
        if (!components[neigbour]) {
            dfs(neigbour, current_component, tree, components, new_component);
        }
    }
}

bool checkEdgeCase(std::vector<std::vector<int>>& tree, int n, std::vector<int>& cnt_friendly_friends) {
    for (int i = 1; i <= n; i++) {
        size_t cnt = 0;
        for (const auto& neighbour : tree[i]) {
            if (tree[neighbour].size() >= 2) {
                cnt++;
            }
            if (cnt >= 3) {
                return true;
            }
        }
        cnt_friendly_friends[i] = cnt;
    }
    return false;
}

void addEdge(std::vector<std::vector<int>>& tree, int from, int to) {
    tree[from].push_back(to);
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> tree(n + 1);
    std::vector<bool> has_neighbour(n + 1, false);
    for (int i = 0; i < m; i++) {
        int from, to;
        std::cin >> from >> to;
        addEdge(tree, from, to);
        addEdge(tree, to, from);
        has_neighbour[from] = true;
        has_neighbour[to] = true;
    }
    int lonely = 0;
    for (int i = 1; i <= n; i++) {
        if (!has_neighbour[i]) {
            lonely++;
        }
    }
    std::vector<int> vis(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && has_neighbour[i]) {
            if (hasCycle(tree, i, -1, vis)) {
                std::cout << 0;
                return 0;
            }
        }
    }
    std::vector<int> cnt_friendly_friends(n + 1);
    if (checkEdgeCase(tree, n, cnt_friendly_friends)) {
        std::cout << 0;
        return 0;
    }
    std::vector<long long> factorials = precomputeFactorials(n, k);
    std::vector<std::vector<int>> components;
    int current_component = 0;
    vis = {};
    vis.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0 && has_neighbour[i]) {
            current_component++;
            std::vector<int> new_component;
            dfs(i, current_component, tree, vis, new_component);
            components.push_back(new_component);
        }
    }
    long long ans = 1;
    std::vector<int> visited(n + 1);
    for (const auto& component : components) {
        ans = (ans * 2) % k;
        int cnt = 0;
        for (const auto& vertex : component) {
            if (tree[vertex].size() == 1) {
                continue;
            }
            int visited_lonely = 0;
            int visited_friendly = 0;
            for (const auto& neighbour : tree[vertex]) {
                if (visited[neighbour]) {
                    if (tree[neighbour].size() == 1) {
                        visited_lonely++;
                    } else if (tree[neighbour].size() >= 2) {
                        visited_friendly++;
                    }
                }
            }
            cnt++;
            int remaining_nodes = tree[vertex].size() - visited_friendly - visited_lonely;
            int friendly_diff = cnt_friendly_friends[vertex] - visited_friendly;
            ans = (ans * factorials[remaining_nodes - friendly_diff]) % k;
            for (const auto& neighbour : tree[vertex]) {
                visited[neighbour] = 1;
            }
            visited[vertex] = 1;
        }
        if (cnt >= 2) {
            ans = (ans * 2) % k;
        }
    }
    long long cur = 1;
    if (lonely != 0) {
        for (int i = n - lonely + 2; i <= n + 1; i++) {
            cur = (cur * (i % k)) % k;
        }
    }
    ans = (ans * factorials[current_component]) % k;
    ans = (ans * cur) % k;
    std::cout << ans  << ' ';
    return 0;
}
