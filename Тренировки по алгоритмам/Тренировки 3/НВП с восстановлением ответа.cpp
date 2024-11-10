#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    std::vector<std::pair<int, std::vector<int>>> lis(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
        lis[i].second.push_back(arr[i]);
        lis[i].first = 1;
    }
    int max_len = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i].first <= lis[j].first) {
                lis[i].second = lis[j].second;
                lis[i].second.push_back(arr[i]);
                lis[i].first = lis[j].first + 1;
            }
        }
        if (lis[i].first > max_len) {
            max_len = lis[i].first;
        }
    }
    for (int i = 0; i < n; i++) {
        if (lis[i].second.size() == max_len) {
            for (auto el : lis[i].second) {
                std::cout << el << ' ';
            }
            break;
        }
    }
    return 0;
}