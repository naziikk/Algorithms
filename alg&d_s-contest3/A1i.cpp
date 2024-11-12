#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

struct Circle {
    double x;
    double y;
    double radius;
};

bool isInsideCircle(const Circle& circle, double x, double y) {
    return (x - circle.x) * (x - circle.x) + (y - circle.y) * (y - circle.y) <= circle.radius * circle.radius;
}

int main() {
    std::vector<Circle> circles(3);
    for (int i = 0; i < 3; i++) {
        std::cin >> circles[i].x >> circles[i].y >> circles[i].radius;
    }
    double leftmost_x = 0.0;
    double rightmost_x = 1.0;
    double lowest_y = 0.0;
    double highest_y = 1.0;
    for (const auto& circle : circles) {
        leftmost_x = std::min(leftmost_x, circle.x - circle.radius);
        rightmost_x = std::max(rightmost_x, circle.x + circle.radius);
        lowest_y = std::min(lowest_y, circle.y - circle.radius);
        highest_y = std::max(highest_y, circle.y + circle.radius);
    }
    const int n = 10000000;
    std::mt19937 gen(0);
    std::uniform_real_distribution<> distrib_x(leftmost_x, rightmost_x);
    std::uniform_real_distribution<> distrib_y(lowest_y, highest_y);

    int inside_count = 0;
    for (int i = 0; i < n; i++) {
        double x = distrib_x(gen);
        double y = distrib_y(gen);
        if (isInsideCircle(circles[0], x, y) && isInsideCircle(circles[1], x, y) && isInsideCircle(circles[2], x, y)) {
            inside_count++;
        }
    }
    double sq = (rightmost_x - leftmost_x) * (highest_y - lowest_y);
    double answer = static_cast<double>(inside_count) / n * sq;
    std::cout << answer;
    return 0;
}