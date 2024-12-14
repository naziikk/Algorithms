#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main() {
    std::unordered_map<char, std::string> actions;
    std::vector<char> directions = {'N', 'S', 'W', 'E', 'U', 'D'};
    for (int i = 0; i < 6; i++) {
        std::string path;
        std::getline(std::cin, path);
        actions[directions[i]] = path;
    }
    char direction;
    int amount;
    std::cin >> direction >> amount;
    std::vector<std::vector<long long>> dp(amount + 1, std::vector<long long>(directions.size(), 0));
    for (int i = 0; i < 6; i++) {
        dp[1][i] = 1;
    }
    for (int i = 2; i <= amount; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) {
                int count_matches = std::count(actions[directions[k]].begin(),
                                               actions[directions[k]].end(), directions[j]);
                dp[i][j] += dp[i - 1][k] * count_matches;
            }
        }
    }
    int idx = std::find(directions.begin(), directions.end(), direction) - directions.begin();
    std::cout << dp[amount][idx];
    return 0;
}