#include <unordered_map>
#include <vector>
#include <iostream>
#include <regex>
#include <iomanip>
#include <unordered_set>

struct Player {
    int games = 0;
    std::vector<int> total_goals;
    int score_opens = 0;
    std::string team;

    [[nodiscard]] int ScoreOpens() const {
        return score_opens;
    };

    [[nodiscard]] int TotalGoals() const {
        return total_goals.size();
    }

    int TotalGoalsOnMinute(int l, int r) {
        int answer = 0;
        for (auto goal : total_goals) {
            if (goal >= l && goal <= r) {
                 answer++;
            }
        }
        return answer;
    }
};

struct Team {
    int games = 0;
    int score_opens = 0;
    int total_goals = 0;

    [[nodiscard]] double MeanValue() const {
        if (games == 0) {
            return 0;
        }
        return total_goals / static_cast<double>(games);
    }

    [[nodiscard]] int ScoreOpens() const {
         return score_opens;
    };

    [[nodiscard]] int TotalGoals() const {
        return total_goals;
    }
};

void ParseGoals(std::unordered_map<std::string, Player>& player_info, std::unordered_map<std::string, Team>& team_info,
                int total_goals, std::smatch matches, std::string line, int first_cnt, int second_cnt,
                const std::string& first_team, const std::string& second_team) {
    int i = 0;
    std::unordered_set<std::string> set_first_team;
    std::unordered_set<std::string> set_second_team;
    std::string result_opener;
    int min_minute = 100;
    std::string team;
    while (i < total_goals && std::getline(std::cin, line)) {
        if (std::regex_match(line, matches, std::regex(R"(^([\w\s]+)\s+(\d+)')"))) {
            std::string player = matches[1];
            int minute = std::stoi(matches[2]);
            if (i + 1 <= first_cnt) {
                if (minute < min_minute) {
                    min_minute = minute;
                    result_opener = player;
                    team = first_team;
                }
                player_info[player].team = first_team;
                if (set_first_team.find(player) == set_first_team.end()) {
                    player_info[player].games++;
                    set_first_team.insert(player);
                }
                player_info[player].total_goals.push_back(minute);
            } else {
                if (minute < min_minute) {
                    min_minute = minute;
                    result_opener = player;
                    team = second_team;
                }
                player_info[player].team = second_team;
                if (set_second_team.find(player) == set_second_team.end()) {
                    player_info[player].games++;
                    set_second_team.insert(player);
                }
                player_info[player].total_goals.push_back(minute);
            }
        }
        i++;
    }
    team_info[team].score_opens++;
    player_info[result_opener].score_opens++;
}

int main() {
    std::unordered_map<std::string, Player> player_info;
    std::unordered_map<std::string, Team> team_info;
    std::string line;
    std::regex pattern("^\"([^\"]+)\"\\s*-\\s*\"([^\"]+)\"\\s*(\\d+):(\\d+)$");
    std::smatch matches;
    while (std::getline(std::cin, line)) {
        if (std::regex_match(line, matches, pattern)) {
            std::string team1 = matches[1];
            std::string team2 = matches[2];
            int score1 = std::stoi(matches[3]);
            int score2 = std::stoi(matches[4]);
            team_info[team1].games++;
            team_info[team1].total_goals += score1;
            team_info[team2].games++;
            team_info[team2].total_goals += score2;
            if (score1 + score2 != 0) {
                ParseGoals(player_info, team_info, score1 + score2, matches, line, score1, score2, team1, team2);
            }

        } else if (std::regex_match(line, matches, std::regex("^Mean goals per game for \"([A-Za-z\\s]+)\"$"))) {
            std::string team = matches[1];
            std::cout << team_info[team].MeanValue() << '\n';
        } else if (std::regex_match(line, matches, std::regex("^Mean goals per game by ([A-Za-z\\s]+)$"))) {
            std::string player = matches[1];
            if (player_info[player].games == 0) {
                std::cout << 0 << '\n';
            } else {
                std::cout << (double) player_info[player].total_goals.size() /
                (double) team_info[player_info[player].team].games << '\n';
            }
        }
        else if (std::regex_match(line, matches, std::regex("^Total goals for \"([A-Za-z\\s]+)\"$"))) {
            std::string team = matches[1];
            std::cout << team_info[team].TotalGoals() << '\n';
        } else if (std::regex_match(line, matches, std::regex("^Total goals by ([A-Za-z\\s]+)$"))) {
            std::string player = matches[1];
            std::cout << player_info[player].TotalGoals() << '\n';
        } else if (std::regex_match(line, matches, std::regex("^Score opens by ([A-Za-z\\s]+)$"))) {
            std::string player = matches[1];
            std::cout << player_info[player].ScoreOpens() << '\n';
        } else if (std::regex_match(line, matches, std::regex("^Score opens by \"([A-Za-z\\s]+)\"$"))) {
            std::string team = matches[1];
            std::cout << team_info[team].ScoreOpens() << '\n';
        } else if (std::regex_match(line, matches, std::regex("^Goals on minute (\\d+) by ([A-Za-z\\s]+)$"))) {
            int minute = std::stoi(matches[1]);
            std::string player = matches[2];
            std::cout << player_info[player].TotalGoalsOnMinute(minute, minute) << '\n';
        } else if (std::regex_match(line, matches, std::regex("^^Goals on last (\\d+) minutes by ([A-Za-z\\s]+)$"))) {
            int minute = std::stoi(matches[1]);
            std::string player = matches[2];
            std::cout << player_info[player].TotalGoalsOnMinute(91 - minute, 90) << '\n';
        } else if (std::regex_match(line, matches, std::regex("^Goals on first (\\d+) minutes by ([A-Za-z\\s]+)$"))) {
            int minute = std::stoi(matches[1]);
            std::string player = matches[2];
            std::cout << player_info[player].TotalGoalsOnMinute(0, minute) << '\n';
        } else {
            std::cout << line << '\n';
        }
    }
    return 0;
}
