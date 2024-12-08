#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

struct Point {
    int x;
    int y;
    int dist;
};

std::vector<std::pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m;

void bfs(std::vector<std::vector<int>>& maze, std::vector<std::vector<int>>& dist) {
    std::queue<Point> q;
    q.push({0, 0, 0});
    dist[0][0] = 0;
    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        for (auto& dir : directions) {
            int x = p.x;
            int y = p.y;
            while (x + dir.first >= 0 && x + dir.first < n &&
                   y + dir.second >= 0 && y + dir.second < m &&
                   maze[x + dir.first][y + dir.second] != 1) {
                x += dir.first;
                y += dir.second;
                if (maze[x][y] == 2) {
                    break;
                }
            }
            if (dist[x][y] > p.dist + 1) {
                dist[x][y] = p.dist + 1;
                q.push({x, y, dist[x][y]});
            }
        }
    }
}

int main() {
    std::cin >> n >> m;
    std::vector<std::vector<int>> maze(n, std::vector<int>(m));
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, INT_MAX));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> maze[i][j];
        }
    }
    bfs(maze, dist);
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == 2) {
                ans = std::min(ans, dist[i][j]);
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
