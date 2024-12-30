struct State {
    int mask;
    int node;
    int distance;
};

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        int all_mask = (1 << n) - 1;
        queue<State> q;
        unordered_set<int> visited;
        for (int i = 0; i < n; i++) {
            q.push({1 << i, i, 0});
            visited.insert((1 << i) * 17 + i);
        }
        while (!q.empty()) {
            auto state = q.front();
            q.pop();
            if (state.mask == all_mask) {
                return state.distance;
            }
            for (const auto& neighbour : graph[state.node]) {
                int temp_mask = state.mask | (1 << neighbour);
                int hash = temp_mask * 17 + neighbour;
                if (visited.find(hash) == visited.end()) {
                    visited.insert(hash);
                    q.push({temp_mask, neighbour, state.distance + 1});
                }
            }
        }
        return -1;
    }
};