#include <vector>
#include <iostream>

struct Edge {
    int to;
    int weight;
};

std::vector<std::vector<Edge>> RestoreGraph(const std::vector<std::vector<int>>& dist) {
    int n = dist.size();
    std::vector<std::vector<Edge>> restored(n);

    for (int i = 0; i < n; i++) {
        if (dist[i][i] != 0) {
            return {};
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            bool is_directed = true;
            for (int k = 0; k < n; k++) {
                if (k != i && k != j && dist[i][j] == dist[i][k] + dist[k][j]) {
                    is_directed = false;
                    break;
                }
            }
            if (is_directed) {
                restored[i].push_back({j, dist[i][j]});
            }
        }
    }

    return restored;
}

int main() {

}