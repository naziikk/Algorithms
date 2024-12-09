#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> s_arr(128);
    std::string s;
    std::cin >> s;
    for (int i = 0; i < n; i++) {
        s_arr[s[i]]++;
    }
    std::string t;
    std::cin >> t;
    std::vector<int> t_arr(128);
    int l = 0;
    int ans = 0;
    for (int i = 0; i < m; i++) {
        t_arr[t[i]]++;
        if (i - l + 1 == n) {
            if (s_arr == t_arr) {
                ans++;
            }
            t_arr[t[l]]--;
            l++;
        }
    }
    std::cout << ans;
    return 0;
}