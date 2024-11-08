#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

struct Player {
    int x, y, v;
};

double timeToReach(double x, double y, const Player& player) {
    double distance = std::sqrt((x - player.x) * (x - player.x) + (y - player.y) * (y - player.y));
    return distance / player.v;
}

bool canHitWithMinTime(double minTime, double D, const std::vector<Player>& players) {
    const int steps = 360; // Разделяем углы на 360 шагов
    for (int angle = 0; angle < steps; ++angle) {
        double radian = angle * M_PI / 180.0;
        double low = 0, high = D;

        while (high - low > 1e-6) {
            double r = (low + high) / 2;
            double x = r * cos(radian);
            double y = r * sin(radian);
            if (y < 0) {
                low = r;
                continue;
            }

            bool canReach = true;
            for (const auto& player : players) {
                if (timeToReach(x, y, player) < minTime) {
                    canReach = false;
                    break;
                }
            }

            if (canReach)
                low = r;
            else
                high = r;
        }

        double x = low * cos(radian);
        double y = low * sin(radian);
        if (y >= 0) {
            bool canReach = true;
            for (const auto& player : players) {
                if (timeToReach(x, y, player) < minTime) {
                    canReach = false;
                    break;
                }
            }
            if (canReach)
                return true;
        }
    }
    return false;
}

int main() {
    double D;
    int N;
    std::cin >> D >> N;

    std::vector<Player> players(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> players[i].x >> players[i].y >> players[i].v;
    }

    double left = 0, right = D;
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        if (canHitWithMinTime(mid, D, players)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    std::cout << std::fixed << std::setprecision(6) << left << std::endl;
    return 0;
}