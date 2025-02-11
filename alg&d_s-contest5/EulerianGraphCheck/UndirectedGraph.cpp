#include <iostream>
#include <vector>

class EulerianUndirectedGraph {
    std::vector<std::vector<int>> graph;
    std::vector<int> degree;
    std::vector<int> components_distribution;
    int n;

public:
    explicit EulerianUndirectedGraph(const std::vector<std::vector<int>>& graph) : graph(graph) {
        n = graph.size();
        degree.resize(n);
        components_distribution.resize(n);
        for (int i = 0; i < n; i++) {
            degree[i] = graph[i].size();
        }
    }

    // поддержка обхода в глубину
    void dfs(int vertex, std::vector<int>& visited) {
        visited[vertex] = 1;
        for (const auto& neighbour : graph[vertex]) {
            if (!visited[neighbour]) {
                dfs(neighbour, visited);
            }
        }
    }

    bool DegreeCheck() {
        for (int i = 0; i < n; i++) {
            if (degree[i] % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    void GetComponents(int vertex, std::vector<int>& components, int current_component) {
        components[vertex] = current_component;
        for (const auto& neighbour : graph[vertex]) {
            if (components[neighbour] == -1) {
                GetComponents(neighbour, components, current_component);
            }
        }
    }

    bool IsEulerian() {
        // определяем от нулевой вершины все достижимые вершины
        GetComponents(0, components_distribution, 1);
        // проходимся по всем вершинам и проверяем, что она в той же компоненте связности
        for (size_t i = 0; i < n; i++) {
            if (components_distribution[i] != 1) {
                // если это не так, то граф не является Эйлеровым
                return false;
            }
        }
        // проверяем степени вершин
        // если существует граф с нечетной степенью, граф не Эйлеров
        return DegreeCheck();
    }
};