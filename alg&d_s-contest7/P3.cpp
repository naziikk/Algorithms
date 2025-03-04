#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

class Network {
    int n;
    std::vector<std::unordered_map<int, int>> capacity;
    std::vector<std::unordered_map<int, int>> flow;
    std::vector<int> level;
    std::vector<int> ptr;

public:
    std::vector<std::vector<int>> adj;

    Network(int n) : n(n), capacity(n), flow(n), adj(n), level(n), ptr(n) {}

    void add_edge(int from, int to, int cap) {
        capacity[from][to] += cap;
        capacity[to][from] += cap;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }

    bool bfs(int src, int dst) {
        level.assign(n, -1);
        level[src] = 0;
        std::queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (const auto& neighbour : adj[node]) {
                if (level[neighbour] == -1 && flow[node][neighbour] < capacity[node][neighbour]) {
                    level[neighbour] = level[node] + 1;
                    q.push(neighbour);
                }
            }
        }
        return level[dst] != -1;
    }

    int dfs(int src, int dst, int pushed) {
        if (pushed == 0) return 0;
        if (src == dst) return pushed;

        for (int& i = ptr[src]; i < adj[src].size(); i++) {
            int neighbour = adj[src][i];

            if (level[neighbour] != level[src] + 1 || flow[src][neighbour] == capacity[src][neighbour])
                continue;

            int tr = dfs(neighbour, dst, std::min(pushed, capacity[src][neighbour] - flow[src][neighbour]));
            if (tr == 0) continue;

            flow[src][neighbour] += tr;
            flow[neighbour][src] -= tr;
            return tr;
        }
        return 0;
    }

    long long GetMaxFlow(int src, int dst) {
        long long max_flow = 0;
        flow.clear();
        flow.resize(n);

        while (bfs(src, dst)) {
            ptr.assign(n, 0);
            while (int pushed = dfs(src, dst, INT_MAX)) {
                max_flow += pushed;
            }
        }
        return max_flow;
    }
};

std::unordered_map<std::string, int> name_to_number;
int current_number = 0;

int ConvertToNumber(const std::string& name) {
    if (name_to_number.find(name) == name_to_number.end()) {
        name_to_number[name] = current_number++;
    }
    return name_to_number[name];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, k;
    std::cin >> n >> m >> k;

    Network network(n);

    for (int i = 0; i < m; ++i) {
        std::string from, to;
        std::cin >> from >> to;
        int u = ConvertToNumber(from);
        int v = ConvertToNumber(to);
        network.add_edge(u, v, 1);
    }

    int positive_cnt = 0;
    for (int i = 0; i < k; i++) {
        std::string from, to;
        std::cin >> from >> to;
        if (positive_cnt > 1) {
            std::cout << 0 << '\n';
            continue;
        }
        int u = ConvertToNumber(from);
        int v = ConvertToNumber(to);
        if (u == v) {
            std::cout << 0 << '\n';
            continue;
        }
        int value = network.GetMaxFlow(u, v);
        std::cout << value << '\n';
        positive_cnt++;
    }

    return 0;
}