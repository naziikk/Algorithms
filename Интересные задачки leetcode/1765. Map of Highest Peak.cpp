class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        queue<pair<int, int>> q;
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    q.push({i, j});
                } else {
                    grid[i][j] = -1;
                }
            }
        }

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto& [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == -1) {
                    grid[nx][ny] = grid[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return grid;
    }
};