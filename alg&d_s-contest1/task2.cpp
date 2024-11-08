#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        arr[i] = num;
    }
    int ans = 0;
    std::vector<int> temp;
    int k = 1;
    std::unordered_map<int, std::set<std::vector<int>>> mp;
    for (int i = 0; i < n; i++) {
        for (int j = k; j < n; j++) {
            temp.push_back(arr[j]);
        }
        for (int j = 0; j < k; j++) {
            temp.push_back(arr[j]);
        }
        int cur = 0;
        for (int j = 0; j < n; j++) {
            if (temp[j] != arr[j]) {
                cur++;
            }
        }
        ans = std::max(ans, cur);
        mp[cur].insert(temp);
        temp.clear();
        k++;
    }
    int res = mp[ans].size();
    std::cout << res;
    return 0;
}