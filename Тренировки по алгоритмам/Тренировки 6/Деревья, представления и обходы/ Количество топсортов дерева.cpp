#include <iostream>
#include <vector>
const int mod = 1e9 + 7;

struct Edge {
    int number;
    int direction;

    Edge(int number, int direction) : number(number), direction(direction){};
};

long long computeCombinations(const std::vector<std::vector<long long>>& combinations, int i, int j,
                              size_t sum_size, size_t size_child, const std::vector<long long>& dp_current,
                              const std::vector<long long>& ps, int direction) {
    long long current = 1;
    current = ((long long) current * combinations[sum_size - 1 - i - j][size_child - j]) % mod;
    current = ((long long) current * dp_current[i]) % mod;
    current = ((long long) current * combinations[i + j][j]) % mod;
    if (direction == 0) {
        current = ((long long) current * ((ps.back() - ps[j] + mod) % mod)) % mod;
    } else {
        current = ((long long) current * ps[j]) % mod;
    }
    return current;
}

std::vector<long long> dfs(const std::vector<std::vector<Edge>>& tree, int vertex, int prev,
                     const std::vector<std::vector<long long>>& combinations) {
    std::vector<long long> dp_current;
    dp_current.push_back(1);
    for (const auto& [neighbor, direction] : tree[vertex]) {
        if (neighbor != prev) {
            std::vector<long long> dp_child = dfs(tree, neighbor, vertex, combinations);
            std::vector<long long> ps;
            ps.push_back(0);
            for (size_t i = 0; i < dp_child.size(); i++) {
                ps.push_back((ps.back() + dp_child[i]) % mod);
            }
            size_t size_current = dp_current.size();
            size_t size_child = dp_child.size();
            size_t sum_size = size_child + size_current;
            std::vector<long long> dp_new(sum_size, 0);
            for (size_t j = 0; j <= size_child; j++) {
                for (size_t i = 0; i < size_current; i++) {
                    long long current = computeCombinations(combinations, i, j, sum_size,
                                                             size_child, dp_current, ps, direction);
                    dp_new[j + i] = (dp_new[j + i] + current) % mod;
                }
            }
            dp_current = dp_new;
        }
    }
    return dp_current;
}

std::vector<std::vector<long long>> precomputeCombinations(int n) {
    std::vector<std::vector<long long>> combinations(n, std::vector<long long>(n));
    for (int i = 0; i < n; i++) {
        combinations[i][0] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= i; j++) {
            combinations[i][j] = (combinations[i - 1][j] + combinations[i - 1][j - 1]) % mod;
        }
    }
    return combinations;
}

void addEdge(std::vector<std::vector<Edge>>& tree, int from, int to, int direction) {
    tree[from].emplace_back(to, direction);
}

int main() {
    int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << 1;
        return 0;
    }
    std::vector<std::vector<Edge>> tree(n + 1);
    for (int i = 1; i < n; i++) {
        int from, to;
        std::cin >> from >> to;
        addEdge(tree, from, to, 0);
        addEdge(tree, to, from, 1);
    }
    int root = 1;
    int prev = -1;
    std::vector<std::vector<long long>> combinations = precomputeCombinations(3010);
    std::vector<long long> dp = dfs(tree, root, prev, combinations);
    long long ans = 0;
    for (const auto& value : dp) {
        ans = (ans + value) % mod;
    }
    std::cout << ans;
    return 0;
}