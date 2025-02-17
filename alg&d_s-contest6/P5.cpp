#include <iostream>
#include <vector>

void FloydWarshall(long long n, std::vector<std::vector<long long>>& dist) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (dist[j][i] != LLONG_MAX && dist[i][k] != LLONG_MAX) {
                    if (dist[j][k] == 0 || dist[j][k] > dist[j][i] + dist[i][k]) {
                        dist[j][k] = dist[j][i] + dist[i][k];
                    }
                }
            }
        }
    }
}

int main() {
    int n, edges_count;
    std::cin >> n >> edges_count;
    std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, LLONG_MAX));
    for (int i = 0; i < edges_count; i++) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        dist[from][to] = weight;
    }
    FloydWarshall(n, dist);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                std::string weight = dist[i][j] == LLONG_MAX ? "-1" : std::to_string(dist[i][j]);
                std::cout << i << ' ' << j << ' ' << weight << '\n';
            }
        }
    }
    return 0;
}