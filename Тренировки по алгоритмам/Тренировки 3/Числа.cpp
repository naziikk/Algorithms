#include <iostream>
#include <queue>
#include <unordered_set>
#include <climits>
#include <vector>

std::vector<std::string> ans;
int len_ans = INT_MAX;
std::unordered_set<std::string> visited;
void bfs(std::string from, std::string to) {
    std::queue<std::string> q;
    std::unordered_map<std::string, std::string> parent;
    q.push(from);
    parent[from] = "";
    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        if (current == to) {
            ans.clear();
            for (std::string at = to; !at.empty(); at = parent[at]) {
                ans.push_back(at);
            }
            std::reverse(ans.begin(), ans.end());
            return;
        }
        if (visited.count(current)) {
            continue;
        }
        visited.insert(current);
        if (current[0] != '9') {
            std::string temp = std::to_string(current[0] - '0' + 1) + current.substr(1);
            if (!parent.count(temp)) {
                parent[temp] = current;
                q.push(temp);
            }
        }

        if (current.back() != '1') {
            std::string temp = current.substr(0, current.size() - 1) + std::to_string(current.back() - '0' - 1);
            if (!parent.count(temp)) {
                parent[temp] = current;
                q.push(temp);
            }
        }
        std::string shift_right = current.back() + current.substr(0, current.size() - 1);
        if (!parent.count(shift_right)) {
            parent[shift_right] = current;
            q.push(shift_right);
        }
        std::string shift_left = current.substr(1) + current[0];
        if (!parent.count(shift_left)) {
            parent[shift_left] = current;
            q.push(shift_left);
        }
    }
}

int main() {
    std::string from;
    std::string to;
    std::cin >> from >> to;
    bfs(from, to);
    for (auto move : ans) {
        std::cout << move << '\n';
    }
    return 0;
}