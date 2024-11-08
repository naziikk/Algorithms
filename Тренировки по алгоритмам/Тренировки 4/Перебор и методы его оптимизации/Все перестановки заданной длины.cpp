#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> ans;
void backtrack(std::vector<int>& arr, int i) {
    if (i == arr.size()) {
        ans.push_back(arr);
        return;
    }
    for (int j = i; j < arr.size(); j++) {
        std::swap(arr[i], arr[j]);
        backtrack(arr, i + 1);
        std::swap(arr[i], arr[j]);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr;
    for (int i = 1; i <= n; i++) {
        arr.push_back(i);
    }
    backtrack(arr, 0);
    std::sort(ans.begin(), ans.end());
    for (auto array : ans) {
        for (auto el : array) {
            std::cout << el;
        }
        std::cout << '\n';
    }
    return 0;
}