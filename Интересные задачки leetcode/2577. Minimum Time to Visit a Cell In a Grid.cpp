#include <iostream>
#include <queue>
#include <vector>
#include <climits>

struct Cell {
    int x, y, time;

    bool operator>(const Cell& other) const {
        return time > other.time;
    }
};

class Solution {
public:
    int minimumTime(std::vector<std::vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        if (grid[0][1] > 1 && grid[1][0] > 1) {
            return -1;
        }
        std::vector<std::vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INT_MAX));
        std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pq;

        pq.push({0, 0, 0});
        dist[0][0] = 0;
        while (!pq.empty()) {
            auto [x, y, time] = pq.top();
            pq.pop();
            if (time > dist[x][y]) {
                continue;
            }
            for (const auto& dir : directions) {
                int new_x = x + dir[0];
                int new_y = y + dir[1];
                if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols) {
                    int next_time = time + 1;
                    if (next_time < grid[new_x][new_y]) {
                        int wait = (grid[new_x][new_y] - next_time) % 2;
                        next_time = grid[new_x][new_y] + wait;
                    }
                    if (next_time < dist[new_x][new_y]) {
                        dist[new_x][new_y] = next_time;
                        pq.push({new_x, new_y, next_time});
                    }
                }
            }
        }
        int result = dist[rows - 1][cols - 1];
        return result == INT_MAX ? -1 : result;
    }
};
