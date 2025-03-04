#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int vertex;
    double cost;
    double heuristic_priority;

    bool operator>(const Node& other ) const {
        return heuristic_priority > other.heuristic_priority;
    }
};

class AStar {
    int n;
    std::vector<std::vector<int>> graph;
    std::vector<std::pair<int, int>> coord;

public:
    AStar(int n) : n(n), graph(n), coord(n) {}

    void AddEdge(int from, int to) {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    void SetCoord(int vertex, int x, int y) {
        coord[vertex] = {x, y};
    }

    double GetDistance(int from, int to) {
        return std::sqrt(std::pow(coord[from].first - coord[to].first, 2) + std::pow(coord[from].second - coord[to].second, 2));
    }

    int GetMinPath(int src, int dst) {
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
        std::vector<double> dist(n, std::numeric_limits<double>::max());

        dist[src] = 0;
        pq.push({src, 0, GetDistance(src, dst)});
        while (!pq.empty()) {
            auto [vertex, cost, heuristic_priority] = pq.top();
            pq.pop();

            if (vertex == dst) {
                return cost;
            }

            for (const auto& neighbour : graph[vertex]) {
                double new_cost = cost + GetDistance(vertex, neighbour);
                if (new_cost < dist[neighbour]) {
                    dist[neighbour] = new_cost;
                    pq.push({neighbour, new_cost, new_cost + GetDistance(neighbour, dst)});
                }
            }
        }
        return -1;
    }
};