#include <iostream>
#include <vector>
#include <queue>
#include <list>

int minimumObstacles(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::vector<int>> dist(m, std::vector<int>(n, INT_MAX));
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>,
            std::greater<std::pair<int, std::pair<int, int>>>> pq;
    dist[0][0] = 0;
    pq.push({0, {0, 0}});
    while (!pq.empty()) {
        auto [distance, coords] = pq.top();
        auto [i, j] = coords;
        pq.pop();
        for (int idx = 0; idx < 4; idx++) {
            int new_i = i + directions[idx].first;
            int new_j = j + directions[idx].second;
            if (new_i >= 0 && new_i < m && new_j >= 0 && new_j < n) {
                int new_dist = distance + (grid[new_i][new_j] == 1 ? 1 : 0);
                if (new_dist < dist[new_i][new_j]) {
                    dist[new_i][new_j] = new_dist;
                    pq.push({new_dist, {new_i, new_j}});
                }
            }
        }
    }
    return dist[m - 1][n - 1];
}

int main() {
    std::atomic<int> a;
    std::cout << std::atomic<double>::is_always_lock_free;
}