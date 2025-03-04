#include <iostream>
#include <vector>
#include <queue>

class Network {
    int n;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;
    std::vector<int> level;
    std::vector<int> ptr;

public:
    Network(int n) : n(n), capacity(n, std::vector<int>(n)), flow(n, std::vector<int>(n)), level(n), ptr(n) {}

    void add_edge(int from, int to, int cap) {
        capacity[from][to] += cap;
    }

    bool bfs(int src, int dst) {
        level.assign(n, -1);
        level[src] = 0;
        std::queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbour = 0; neighbour < n; neighbour++) {
                if (level[neighbour] == -1 && flow[node][neighbour] < capacity[node][neighbour]) {
                    level[neighbour] = level[node] + 1;
                    q.push(neighbour);
                }
            }
        }
        return level[dst] != -1;
    }

    int dfs(int src, int dist, int pushed) {
        if (pushed == 0) {
            return 0;
        }
        if (src == dist) {
            return pushed;
        }

        for (int& neighbour = ptr[src]; neighbour < n; neighbour++) {
            if (level[neighbour] != level[src] + 1 || flow[src][neighbour] == capacity[src][neighbour]) {
                continue;
            }

            int tr = dfs(neighbour, dist, std::min(pushed, capacity[src][neighbour] - flow[src][neighbour]));
            if (tr == 0) {
                continue;
            }
            flow[src][neighbour] += tr;
            flow[neighbour][src] -= tr;
            return tr;
        }
        return 0;
    }

    long long GetMaxFlow(int src, int dst) {
        long long max_flow = 0;
        while (bfs(src, dst)) {
            ptr.assign(n, 0);
            while (int pushed = dfs(src, dst, INT_MAX)) {
                max_flow += pushed;
            }
        }
        return max_flow;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Network network(n);

    for (int i = 0; i < m; ++i) {
        int from, to, flow;
        std::cin >> from >> to >> flow;
        --from, --to;
        network.add_edge(from, to, flow);
    }

    std::cout << network.GetMaxFlow(0, n - 1);
    return 0;
}