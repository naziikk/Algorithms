#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

bool isCorrect(const std::vector<long long>& speed_per_time, double mid, int l) {
    size_t j = 0;
    double f_dist = 0.0;
    double s_dist = 0.0;
    for (size_t i = 0; i < speed_per_time.size(); i++) {
        if (i >= mid - 1) {
            f_dist += speed_per_time[i];
            s_dist += speed_per_time[j] * (std::ceil(mid) - mid);
            if (f_dist - s_dist <= l) {
                return false;
            }
            s_dist -= speed_per_time[j] * (std::ceil(mid) - mid);
            s_dist += speed_per_time[j];
            j++;
        }
        else {
            f_dist += speed_per_time[i];
        }
    }
    return true;
}

int main() {
    int l, n;
    std::cin >> l >> n;
    std::vector<std::vector<long long>> arr(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int t, v;
        std::cin >> t >> v;
        arr[i] = {t, v};
        sum += t;
    }
    std::vector<long long> speed_per_time(sum);
    int k = 0;
    for (auto & i : arr) {
        for (int j = 0; j < i[0]; j++) {
            speed_per_time[k] = i[1];
            k++;
        }
    }
    double left = 0;
    auto right = static_cast<double>(sum);
    double ans = INT_MAX;
    while (right - left >= 1e-3) {
        double mid = (left + right) / 2;
        if (isCorrect(speed_per_time, mid, l)) {
            ans = std::min(ans, mid);
            right = mid;
        }
        else {
            left = mid;
        }
    }
    if (ans == INT_MAX) {
        ans = sum;
    }
    std::cout << std::fixed << std::setprecision(3) << ans << '\n';
    return 0;
}
