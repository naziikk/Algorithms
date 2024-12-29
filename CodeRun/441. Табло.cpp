#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<std::string, int> players;
    std::string player;
    for (int i = 0; i < n; i++) {
        std::cin >> player;
        players[player] = 0;
    }
    int m;
    std::cin >> m;
    int prev_a = 0;
    int prev_b = 0;
    int maxi = 0;
    std::string winner;
    for (int i = 0; i < m; i++) {
        std::string points;
        std::cin >> points >> player;
        auto it = points.find(':');
        int a = std::stoi(points.substr(0, it));
        int b = std::stoi(points.substr(it + 1));
        players[player] += a - prev_a + b - prev_b;
        prev_a = a;
        prev_b = b;
        if (players[player] > maxi || (players[player] == maxi && player > winner)) {
            maxi = players[player];
            winner = player;
        }
    }
    std::cout << winner << ' ' << maxi;
    return 0;
}