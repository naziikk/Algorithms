#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, crew_cnt, people_per_crew;
    std::cin >> n >> crew_cnt >> people_per_crew;
    std::vector<int> students(n);
    for (int i = 0; i < n; i++) {
        std::cin >> students[i];
    }
    std::sort(students.begin(), students.end());
    long long l = 0;
    long long r = *std::max_element(students.begin(), students.end());
    long long ans = -1;
    while (l <= r) {
        long long mid = (l + r) / 2;
        int current_crew_cnt = 0;
        for (int i = people_per_crew - 1; i < n; i++) {
            if (students[i] - students[i - people_per_crew + 1] <= mid) {
                current_crew_cnt++;
                i += people_per_crew - 1;
            }
        }
        if (current_crew_cnt >= crew_cnt) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    std::cout << ans;
    return 0;
}