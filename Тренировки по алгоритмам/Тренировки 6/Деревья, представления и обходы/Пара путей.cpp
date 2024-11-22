#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

void dfsIn(const std::vector<std::vector<int>>& tree, int vertex, int prev, std::vector<int>& inside_paths, std::vector<int>& dp_in) {
    int first_max = 0;
    int second_max = 0;
    int best = 0;
    for (const auto& neighbor : tree[vertex]) {
        if (neighbor == prev) {
            continue;
        }
        dfsIn(tree, neighbor, vertex, inside_paths, dp_in);
        if (inside_paths[neighbor] > first_max) {
            second_max = first_max;
            first_max = inside_paths[neighbor];
        } else if (inside_paths[neighbor] > second_max) {
            second_max = inside_paths[neighbor];
        }
        best = std::max(best, dp_in[neighbor]);
    }
    inside_paths[vertex] = 1 + first_max;
    dp_in[vertex] = std::max(best, 1 + first_max + second_max);
}

std::vector<int> calculateCur(int vertex, int prev, std::vector<std::vector<int>>& tree, std::vector<int>& inside_paths) {
    int third_max_inside = 0;
    int second_max_inside = 0;
    int first_max_inside = 0;
    for (const auto& neighbor : tree[vertex]) {
        if (neighbor != prev) {
            if (first_max_inside < inside_paths[neighbor]) {
                third_max_inside = second_max_inside;
                second_max_inside = first_max_inside;
                first_max_inside = inside_paths[neighbor];
            } else if (second_max_inside < inside_paths[neighbor]) {
                third_max_inside = second_max_inside;
                second_max_inside = inside_paths[neighbor];
            } else if (third_max_inside < inside_paths[neighbor]) {
                third_max_inside = inside_paths[neighbor];
            }
        }
    }
    return {first_max_inside, second_max_inside, third_max_inside};
}

void dfsOut(std::vector<std::vector<int>>& tree, int vertex, int prev, std::vector<int>& inside_paths,
            std::vector<int>& dp_in, std::vector<int>& dp_out, std::vector<int>& outside_paths) {

    int first_max_dp = 0;
    int second_max_dp = 0;
    for (const auto& neighbor : tree[vertex]) {
        if (neighbor != prev) {
            if (first_max_dp < dp_in[neighbor]) {
                second_max_dp = first_max_dp;
                first_max_dp = dp_in[neighbor];
            } else if (dp_in[neighbor] > second_max_dp) {
                second_max_dp = dp_in[neighbor];
            }
        }
    }
    std::vector<int> precompute = calculateCur(vertex, prev, tree, inside_paths);
    int first_max_inside = precompute[0];
    int second_max_inside = precompute[1];
    int third_max_inside = precompute[2];
    for (const auto& neighbor : tree[vertex]) {
        if (neighbor == prev) {
            continue;
        }
        int first_path = (dp_in[neighbor] == first_max_dp) ? second_max_dp : first_max_dp;
        int second_path, third_path;
        if (inside_paths[neighbor] == first_max_inside) {
            second_path = second_max_inside;
            third_path = third_max_inside;
        } else if (inside_paths[neighbor] == second_max_inside) {
            second_path = first_max_inside;
            third_path = third_max_inside;
        } else {
            second_path = first_max_inside;
            third_path = second_max_inside;
        }
        int fourth_path = outside_paths[vertex];
        if (fourth_path > second_path) {
            third_path = second_path;
            second_path = fourth_path;
        } else if (fourth_path > third_path) {
            third_path = fourth_path;
        }
        outside_paths[neighbor] = second_path + 1;
        dp_out[neighbor] = std::max(std::max(first_path, 1 + second_path + third_path), dp_out[neighbor]);

        dfsOut(tree, neighbor, vertex, inside_paths, dp_in, dp_out, outside_paths);
    }
}

void addEdge(std::vector<std::vector<int>>& tree, int from, int to) {
    tree[from].push_back(to);
}

long long showAns(std::vector<int>& dp_in, std::vector<int>& dp_out, int n) {
    for (int i = 1; i <= n; i++) {
        dp_in[i]--;
        dp_out[i]--;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, static_cast<long long>(dp_in[i]) * dp_out[i]);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> tree(n + 1);
    std::vector<int> dp_out(n + 1);
    std::vector<int> dp_in(n + 1, 1);
    std::vector<int> inside_paths(n + 1);
    std::vector<int> outside_paths(n + 1);
    for (int i = 1; i < n; i++) {
        int from, to;
        std::cin >> from >> to;
        addEdge(tree, from, to);
        addEdge(tree, to, from);
    }
    dfsIn(tree, 1, 0, inside_paths, dp_in);
    dfsOut(tree, 1, 0, inside_paths, dp_in, dp_out, outside_paths);
    std::cout << showAns(dp_in, dp_out, n);
    return 0;
}