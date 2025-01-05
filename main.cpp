#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

void findComponent(int vertex, int prev, const std::vector<std::vector<int>>& graph,
                   std::vector<int>& components, int current_component, int skip_node) {
    components[vertex] = current_component;
    for (const auto& neighbour : graph[vertex]) {
        if (neighbour == prev || components[neighbour] != -1 || neighbour == skip_node) {
            continue;
        }
        findComponent(neighbour, vertex, graph, components, current_component, skip_node);
    }
}

int computeInfectedNodes(int n, int skip_connection, std::vector<std::vector<int>>& graph, std::vector<int>& initial) {
    std::vector<int> components(n, -1);
    int current_component = 1;
    for (int i = 0; i < n; i++) {
        if (i == skip_connection) {
            continue;
        }
        if (components[i] == -1) {
            findComponent(i, -1, graph, components, current_component++, skip_connection);
        }
    }
    std::vector<int> component_size(current_component, 0);
    for (const auto& component : components) {
        if (component == -1) {
            continue;
        }
        component_size[component]++;
    }
    std::vector<int> malware_in_component(current_component);
    int result = 0;
    for (const auto& node : initial) {
        if (node == skip_connection) {
            continue;
        }
        malware_in_component[components[node]]++;
        if (malware_in_component[components[node]] == 1) {
            result += component_size[components[node]];
        }
    }
    return result;
}

class Solution {
public:
    int minMalwareSpread(std::vector<std::vector<int>>& grid, std::vector<int>& initial) {
        int n = grid.size();
        std::vector<std::vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] && i != j) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
        std::sort(initial.begin(), initial.end());
        int mini = 0;
        int result_node = initial[0];
        for (const auto& node : initial) {
            int result = computeInfectedNodes(n, node, graph, initial);
            if (result > mini || (result == mini && node < result_node)) {
                mini = result;
                result_node = node;
            }
        }
        return result_node;
    }
};