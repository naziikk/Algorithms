#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

bool specialYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main() {
    std::unordered_map<std::string, int> month_to_number = {
        {"January", 1},
        {"February", 2},
        {"March", 3},
        {"April", 4},
        {"May", 5},
        {"June", 6},
        {"July", 7},
        {"August", 8},
        {"September", 9},
        {"October", 10},
        {"November", 11},
        {"December", 12}
    };
    std::unordered_map<int, std::string> number_to_day = {
        {0, "Monday"},
        {1, "Tuesday"},
        {2, "Wednesday"},
        {3, "Thursday"},
        {4, "Friday"},
        {5, "Saturday"},
        {6, "Sunday"}
    };
    std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::string>>> convert_data;
    std::vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int current_day_of_week = 1;
    for (int year = 1980; year <= 2100; year++) {
        for (int month = 1; month <= 12; month++) {
            int days = days_in_month[month - 1];
            if (month == 2 && specialYear(year)) {
                days = 29;
            }
            for (int day = 1; day <= days; day++) {
                convert_data[year][month][day] = number_to_day[current_day_of_week];
                current_day_of_week = (current_day_of_week + 1) % 7;
            }
        }
    }
    int day, year;
    std::string month;
    while (std::cin >> day && std::cin >> month && std::cin >> year) {
        int month_number_version = month_to_number[month];
        std::cout << convert_data[year][month_number_version][day] << '\n';
    }
    return 0;
}