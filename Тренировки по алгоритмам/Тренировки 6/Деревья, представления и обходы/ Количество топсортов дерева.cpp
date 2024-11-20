#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

vector<vector<int>> binom(int n) {
    vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
    return C;
}

void calc_sz(int u, int parent, const vector<vector<int>>& adj, vector<int>& sz) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != parent) {
            calc_sz(v, u, adj, sz);
            sz[u] += sz[v];
        }
    }
}

int dfs(int u, const vector<vector<int>>& adj, const vector<int>& sz, const vector<vector<int>>& C, vector<int>& dp) {
    dp[u] = 1;
    int total_sz = 0;

    for (int v : adj[u]) {
        if (dp[v] == -1) {
            dfs(v, adj, sz, C, dp);
        }
        total_sz += sz[v];
        dp[u] = (long long)dp[u] * dp[v] % MOD * C[total_sz][sz[v]] % MOD;
    }

    return dp[u];
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    vector<int> sz(n + 1, 0);
    calc_sz(1, 0, adj, sz);

    vector<vector<int>> C = binom(n);

    vector<int> dp(n + 1, -1); // dp[u] — количество топологических сортировок поддерева u
    dp[1] = dfs(1, adj, sz, C, dp);

    cout << dp[1] << endl;

    return 0;
}