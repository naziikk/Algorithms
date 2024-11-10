#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

long long TimeToSeconds(const std::string& time) {
    int hours = std::stoi(time.substr(0, 2));
    int minutes = std::stoi(time.substr(3, 2));
    int seconds = std::stoi(time.substr(6, 2));
    return hours * 3600 + minutes * 60 + seconds;
}

std::string SecondsToTime(long long seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int sec = seconds % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << sec;

    return oss.str();
}

int main() {
    std::string a, b, c;
    std::cin >> a >> b >> c;
    long long day_seconds = 24 * 60 * 60;
    long long seconds_a = TimeToSeconds(a);
    long long seconds_b = TimeToSeconds(b);
    long long seconds_c = TimeToSeconds(c);
    if (seconds_c < seconds_a) {
        seconds_c += day_seconds;
    }
    long long difference = (seconds_c - seconds_a + 1) / 2;
    seconds_b += difference;
    seconds_b %= day_seconds;
    std::cout << SecondsToTime(seconds_b);
    return 0;
}