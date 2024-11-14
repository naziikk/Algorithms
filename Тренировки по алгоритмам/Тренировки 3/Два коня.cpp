#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <queue>
#include <set>

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return (x == other.x) ? (y < other.y) : (x < other.x);
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

void bfs(const Point& coordinates, std::map<Point, int>& distances) {
    std::vector<Point> directions = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};
    std::queue<std::pair<Point, int>> queue;
    queue.emplace(coordinates, 0);
    distances[coordinates] = 0;
    std::set<Point> visited;
    while (!queue.empty()) {
        auto [current_point, dist] = queue.front();
        queue.pop();
        if (visited.count(current_point)) {
            continue;
        }
        visited.insert(current_point);
        for (const Point& direction : directions) {
            Point next = {current_point.x + direction.x, current_point.y + direction.y};
            if (next.x >= 0 && next.x < 8 && next.y >= 0 && next.y < 8) {
               if (!distances.count(next) || distances[next] > dist + 1) {
                    distances[next] = dist + 1;
                    queue.emplace(next, dist + 1);
                }
            }
        }
    }
}

int main() {
    std::string first, second;
    std::cin >> first >> second;
    Point first_coordinates = {first[0] - 'a', first[1] - '1'};
    Point second_coordinates = {second[0] - 'a', second[1] - '1'};
    if (first_coordinates == second_coordinates) {
        std::cout << 0;
        return 0;
    }
    std::map<Point, int> first_distances;
    std::map<Point, int> second_distances;
    bfs(first_coordinates, first_distances);
    bfs(second_coordinates, second_distances);
    int ans = INT_MAX;
    for (int i = 0; i <= 8; i++) {
        for (int j = 0; j < 8; j++) {
            Point current = {i, j};
            if (first_distances[current] != 0 && first_distances[current] == second_distances[current]) {
               ans = std::min(ans, first_distances[current]);
            }
        }
    }
    if (ans == INT_MAX) {
        std::cout << -1;
        return 0;
    }
    std::cout << ans;
    return 0;
}