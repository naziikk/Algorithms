#include <map>
#include <vector>
using namespace std;

class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        const int inf = 1 << 30;
        int minX = inf, maxX = -inf;
        map<pair<int, int>, int> pointCount;
        for (auto& p : points) {
            minX = min(minX, p[0]);
            maxX = max(maxX, p[0]);
            pointCount[{p[0], p[1]}]++;
        }
        int s = minX + maxX;
        for (auto& p : points) {
            std::pair<int, int> mirrored = {s - p[0], p[1]};
            if (pointCount[mirrored] > 0) {
                pointCount[mirrored]--;
            } else {
                return false;
            }
        }
        return true;
    }
};