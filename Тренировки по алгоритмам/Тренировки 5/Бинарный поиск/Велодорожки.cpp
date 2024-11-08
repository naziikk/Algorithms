#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    int x;
    int y;
};

void GetPrefixesAndSuffixes(std::vector<int>& prefix_max, std::vector<int>& prefix_min,
                            std::vector<int>& suffix_max, std::vector<int>& suffix_min, std::vector<Point>& broken_tiles, int n) {
    int min_v = 1e9;
    int max_v = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < n && broken_tiles[j].x == broken_tiles[i].x) {
            min_v = std::min(min_v, broken_tiles[j].y);
            max_v = std::max(max_v, broken_tiles[j].y);
            j++;
        }
        prefix_max[i] = max_v;
        prefix_min[i] = min_v;
    }
    min_v = 1e9;
    max_v = 0;
    j = n - 1;
    for (int i = n; i >= 0; i--) {
        while (j >= 0 && broken_tiles[j].x == broken_tiles[i].x) {
            min_v = std::min(min_v, broken_tiles[j].y);
            max_v = std::max(max_v, broken_tiles[j].y);
            j--;
        }
        suffix_max[i] = max_v;
        suffix_min[i] = min_v;
    }
}

int main() {
    int w, h, n;
    std::cin >> w >> h >> n;
    std::vector<Point> broken_tiles(n);
    for (int i = 0; i < n; i++) {
        std::cin >> broken_tiles[i].x >> broken_tiles[i].y;
    }
    std::sort(broken_tiles.begin(), broken_tiles.end(), [](const Point& f, const Point& s) {
        return f.x < s.x;
    });
    std::vector<int> prefix_max(n);
    std::vector<int> prefix_min(n);
    std::vector<int> suffix_max(n);
    std::vector<int> suffix_min(n);
    GetPrefixesAndSuffixes(prefix_max, prefix_min, suffix_max, suffix_min, broken_tiles, n);
    int l = 1;
    int r = std::min(w, h);
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        int pmx = -1e9;
        int pmn = 1e9;
        bool flag = false;
        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j < n && broken_tiles[j].x < broken_tiles[i].x + mid) {
                j++;
            }
            int maxi = pmx;
            int mini = pmn;
            if (j != n) {
                maxi = std::max(maxi, suffix_max[j]);
                mini = std::min(mini, suffix_min[j]);
            }
            if (maxi - mini < mid) {
                flag = true;
                break;
            }
            pmx = prefix_max[i];
            pmn = prefix_min[i];
        }
        if (flag) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    std::cout << ans;
    return 0;
}