#include <iostream>
#include <vector>
#include <unordered_set>

struct Triangle {
    int first_side;
    int second_side;
    int third_side;
};

void sort(Triangle& triangle) {
    if (triangle.first_side > triangle.second_side) {
        std::swap(triangle.first_side, triangle.second_side);
    }
    if (triangle.second_side > triangle.third_side) {
        std::swap(triangle.second_side, triangle.third_side);
    }
    if (triangle.first_side > triangle.second_side) {
        std::swap(triangle.first_side, triangle.second_side);
    }
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Triangle> triangles(n);
    for (int i = 0; i < n; i++) {
        std::cin >> triangles[i].first_side >> triangles[i].second_side >> triangles[i].third_side;
        int greatest_common_divisor = gcd(gcd(triangles[i].first_side,
                                              triangles[i].second_side), triangles[i].third_side);
        triangles[i].first_side /= greatest_common_divisor;
        triangles[i].second_side /= greatest_common_divisor;
        triangles[i].third_side /= greatest_common_divisor;
        sort(triangles[i]);
    }
    std::unordered_set<std::string> familiar_classes;
    for (const auto& triangle : triangles) {
        std::string representation = std::to_string(triangle.first_side) + " " +
                std::to_string(triangle.second_side) + " " + std::to_string(triangle.third_side);
        familiar_classes.insert(representation);
    }
    std::cout << familiar_classes.size();
    return 0;
}
