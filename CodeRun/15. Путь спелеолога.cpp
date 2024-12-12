#pragma GCC optimize ("O3")
#include <iostream>
#include <queue>
#include <vector>
#include <limits>

int n;

const int empty = 0;
const int wall = -1;

struct Point {
    int x_;
    int y_;
    int z_;

    Point() = default;

    Point(int x, int y, int z) : x_(x), y_(y), z_(z) {}
};

bool isValid(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0 || x >= n
    || y >= n || z >= n) {
        return false;
    }
    return true;
}

Point start;

std::vector<int> x_directions = {0, 0, 0, 0, 1, -1};
std::vector<int> y_directions = {0, 0, 1, -1, 0, 0};
std::vector<int> z_directions = {1, -1, 0, 0, 0, 0};

std::vector<std::vector<std::vector<int>>> cave;

int bfs() {
    std::queue<Point> q;
    q.push(start);
    cave[start.x_][start.y_][start.z_] = 0;
    int ans = 0;
    while (!q.empty()) {
        auto [x, y, z] = q.front();
        q.pop();
        if (x == 0) {
            ans = cave[x][y][z];
            break;
        }
        for (int i = 0; i < 6; i++) {
            int new_x = x + x_directions[i];
            int new_y = y + y_directions[i];
            int new_z = z + z_directions[i];
            if (isValid(new_x, new_y, new_z) && cave[new_x][new_y][new_z] != wall) {
                q.emplace(new_x, new_y, new_z);
                cave[new_x][new_y][new_z] = cave[x][y][z] + 1;
            }
        }
        cave[x][y][z] = -1;
    }
    return ans;
}

int main() {
    std::cin >> n;
    std::cin.ignore();
    cave.assign(n, std::vector<std::vector<int>>(n, std::vector<int>(n, 0)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                char cell;
                std::cin >> cell;
                if (cell == 'S') {
                    start = Point(i, j, k);
                    cave[i][j][k] = empty;
                } else if (cell == '.') {
                    cave[i][j][k] = empty;
                } else {
                    cave[i][j][k] = wall;
                }
            }
        }
        std::cin.ignore();
    }
    std::cout << bfs();
    return 0;
}