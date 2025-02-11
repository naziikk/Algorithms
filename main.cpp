#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> g, rg;
    vector<int> order, component, assignment;
    vector<bool> visited;

    TwoSAT(int _n) : n(_n), g(2 * n), rg(2 * n), assignment(n, -1) {}

    void add_clause(int i1, int e1, int i2, int e2) {
        int x = 2 * i1 + e1, nx = 2 * i1 + (1 - e1);
        int y = 2 * i2 + e2, ny = 2 * i2 + (1 - e2);
        g[nx].push_back(y);
        g[ny].push_back(x);
        rg[y].push_back(nx);
        rg[x].push_back(ny);
    }

    void dfs1(int v) {
        visited[v] = true;
        for (int u : g[v])
            if (!visited[u]) dfs1(u);
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        component[v] = c;
        for (int u : rg[v])
            if (component[u] == -1) dfs2(u, c);
    }

    bool solve() {
        visited.assign(2 * n, false);
        component.assign(2 * n, -1);
        order.clear();

        for (int i = 0; i < 2 * n; i++)
            if (!visited[i]) dfs1(i);

        reverse(order.begin(), order.end());
        int c = 0;
        for (int v : order)
            if (component[v] == -1) dfs2(v, c++);

        for (int i = 0; i < n; i++) {
            if (component[2 * i] == component[2 * i + 1]) return false;
            assignment[i] = (component[2 * i] > component[2 * i + 1]);
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        TwoSAT solver(n);
        for (int i = 0; i < m; i++) {
            int i1, e1, i2, e2;
            cin >> i1 >> e1 >> i2 >> e2;
            solver.add_clause(i1, e1, i2, e2);
        }

        if (solver.solve()) {
            for (int x : solver.assignment) cout << x;
            cout << '\n';
        }
    }
    return 0;
}