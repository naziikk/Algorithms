#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

struct Point {
    int x;
    int y;
    int dist;
};

std::vector<std::pair<int, int>> directions = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

std::vector<std::vector<int>> fixed;
void precomputeDistances(int s, int t, int n, int m) {
    std::queue<Point> q;
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    q.push({s, t, 0});
    fixed[s][t] = 0;
    visited[s][t] = true;

    while (!q.empty()) {
        auto [x, y, dist] = q.front();
        q.pop();
        for (const auto& [dx, dy] : directions) {
            int new_x = x + dx;
            int new_y = y + dy;
            if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m && !visited[new_x][new_y]) {
                fixed[new_x][new_y] = dist + 1;
                visited[new_x][new_y] = true;
                q.push({new_x, new_y, dist + 1});
            }
        }
    }
}


int main() {
    int n, m, s, t, q;
    std::cin >> n >> m >> s >> t >> q;
    s--;
    t--;
    fixed.assign(n, std::vector<int>(m, -1));
    precomputeDistances(s, t, n, m);
    long long ans = 0;
    for (int i = 0; i < q; i++) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        int dist = fixed[x][y];
        if (dist == -1) {
            std::cout << -1;
            return 0;
        }
        ans += dist;
    }
    std::cout << ans << '\n';
    return 0;
}
