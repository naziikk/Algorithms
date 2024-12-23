#include <iostream>
#include <vector>
#include <optional>
#include <unordered_map>
#include <map>
#include <algorithm>

struct Meeting {
    int type;
    int day;
    int idx;
    std::optional<std::string> member;
    std::optional<int> meeting_time;
    std::optional<int> duration;
    std::optional<int> members_cnt;
    std::optional<std::vector<std::string>> members;

    bool operator<(const Meeting& other) const {
        if (type != other.type) {
            return type < other.type;
        }
        if (day != other.day) {
            return day < other.day;
        }
        if (type == 1 && meeting_time && other.meeting_time) {
            if (meeting_time == other.meeting_time) {
                return idx < other.idx;
            }
            return meeting_time < other.meeting_time;
        }
        return idx < other.idx;
    }

};

struct PersonMeetingHistory {
    int meeting_time;
    int duration;
    std::vector<std::string> members;
};

int timeToMinutes(const std::string& time_str) {
    int hour = std::stoi(time_str.substr(0, 2));
    int minute = std::stoi(time_str.substr(3, 2));
    return hour * 60 + minute;
}

bool hasOverlap(const PersonMeetingHistory& last_meeting, int new_meeting_time, int new_meeting_duration) {
    int last_meeting_end_time = last_meeting.meeting_time + last_meeting.duration;
    int new_meeting_end_time = new_meeting_time + new_meeting_duration;
    return new_meeting_time < last_meeting_end_time && new_meeting_end_time > last_meeting.meeting_time;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Meeting> meetings;
    for (int i = 0; i < n; i++) {
        std::string type;
        std::cin >> type;
        if (type == "APPOINT") {
            int day, duration, members_cnt;
            std::string time;
            std::cin >> day >> time >> duration >> members_cnt;
            int convert_time = timeToMinutes(time);

            Meeting meeting = {1, day, i, std::nullopt, convert_time, duration, members_cnt, std::vector<std::string>()};
            for (int j = 0; j < members_cnt; j++) {
                std::string member;
                std::cin >> member;
                meeting.members->push_back(member);
            }
            meetings.push_back(meeting);
        } else {
            int day;
            std::string member;
            std::cin >> day >> member;
            meetings.push_back({2, day, i, member, std::nullopt, std::nullopt, std::nullopt, std::nullopt});
        }
    }
//    std::sort(meetings.begin(), meetings.end());
    std::vector<std::string> ans(n);
    std::unordered_map<std::string, std::map<int, std::vector<PersonMeetingHistory>>> person_history;
    for (const auto& meeting : meetings) {
        if (meeting.type == 1) {
            std::vector<std::string> intersection;
            for (const auto& member : *meeting.members) {
                if (person_history.find(member) != person_history.end()) {
                    const auto& last_meetings = person_history[member][meeting.day];
                    for (const auto& person_meeting : last_meetings) {
                        if (hasOverlap(person_meeting, meeting.meeting_time.value(), meeting.duration.value())) {
                            intersection.push_back(member);
                            break;
                        }
                    }
                }
            }
            if (intersection.empty()) {
                ans[meeting.idx] = "OK\n";
                for (const auto& member : *meeting.members) {
                    person_history[member][meeting.day].push_back({
                                                                          meeting.meeting_time.value(), meeting.duration.value(), meeting.members.value()});
                }
            } else {
                ans[meeting.idx] += "FAIL\n";
                for (const auto& member : intersection) {
                    ans[meeting.idx] += member + ' ';
                }
                ans[meeting.idx].pop_back();
                ans[meeting.idx] += '\n';
            }
        } else {
            bool has_meetings = false;
            std::vector<PersonMeetingHistory> meetings_for_person;
            if (person_history.find(*meeting.member) != person_history.end() &&
                person_history[*meeting.member].find(meeting.day) != person_history[*meeting.member].end()) {
                meetings_for_person = person_history[*meeting.member][meeting.day];
            }
            std::sort(meetings_for_person.begin(), meetings_for_person.end(), [](const PersonMeetingHistory& a, const PersonMeetingHistory& b) {
                return a.meeting_time < b.meeting_time;
            });
            for (const auto& person_meeting : meetings_for_person) {
                has_meetings = true;
                ans[meeting.idx] += (person_meeting.meeting_time / 60 < 10 ? "0" : "") +
                                    std::to_string(person_meeting.meeting_time / 60) + ':';
                ans[meeting.idx] += (person_meeting.meeting_time % 60 < 10 ? "0" : "") +
                                    std::to_string(person_meeting.meeting_time % 60) + ' ';
                ans[meeting.idx] += std::to_string(person_meeting.duration) + ' ';
                for (const auto& member : person_meeting.members) {
                    ans[meeting.idx] += member + ' ';
                }
                ans[meeting.idx].pop_back();
                ans[meeting.idx] += '\n';
            }
            if (!has_meetings) {
                ans[meeting.idx] = "";
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!ans[i].empty()) {
            std::cout << ans[i];
        }
    }

    return 0;
}