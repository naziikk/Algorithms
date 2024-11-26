#include <iostream>
#include <vector>

long long DotProduct(std::vector<std::pair<long long, long long>> a, std::vector<std::pair<long long, long long>> b) {
    if (a.empty()) {
        return 0;
    }
    long long ans = 0;
    int i = 0;
    int j = 0;
    long long first = a[0].second;
    long long second = b[0].second;
    while (i < a.size() && j < b.size()) {
        if (first > second) {
            ans += (a[i].first * b[j].first) * second;
            first -= second;
            j++;
            if (j < b.size()) {
                second = b[j].second;
            }
        } else {
            ans += (a[i].first * b[j].first) * first;
            second -= first;
            i++;
            if (i < a.size()) {
                first = a[i].second;
            }
            if (second == 0) {
                j++;
                if (j < b.size()) {
                    second = b[j].second;
                }
            }
        }
    }
    return ans;
}
