#include <iostream>
#include <vector>
#include <queue>
#include <string>


std::vector<long long> distances;
std::vector<std::vector<int>> paths;

void update(int value, int current, std::queue<int> &q, int cost) {
    if (distances[value] > distances[current] + cost
        || (distances[value] == distances[current] + cost && paths[value].size() > paths[current].size() + 1)) {
        distances[value] = distances[current] + cost;
        paths[value] = paths[current];
        paths[value].push_back(value);
        q.push(value);
    }
}

void bfs(int source, int destination, int n) {
    std::queue<int> q;
    q.push(source);
    distances[source] = 0;
    paths[source] = {source};

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        std::string str = std::to_string(current);
        int len = str.length();

        for (int i = 0; i < len; i++) {
            int shift = 0;
            int cost = 0;
            for (int j = i; j < len; j++) {
                shift = shift * 10 + (str[j] - '0');
                cost += str[j] - '0';

                int next_back = current - shift;
                if (next_back > 0) {
                    update(next_back, current, q, cost);
                }

                int next_front = current + shift;
                if (next_front <= n) {
                    update(next_front, current, q, cost);
                }
            }
        }
    }
}

int main() {
    int n, source, destination;
    std::cin >> n >> source >> destination;

    distances.assign(n + 1, LLONG_MAX);
    paths.resize(n + 1);

    bfs(source, destination, n);

    if (distances[destination] == LLONG_MAX) {
        std::cout << "-1\n";
        return 0;
    }

    std::cout << distances[destination] << '\n';
    std::cout << paths[destination].size() - 1 << '\n';

    for (size_t i = 1; i < paths[destination].size(); i++) {
        int diff = paths[destination][i] - paths[destination][i - 1];
        std::cout << (diff > 0 ? "+" : "") << diff << '\n';
    }
    return 0;
}