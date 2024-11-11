#include <iostream>
#include <vector>
#include <algorithm>

struct Fraction {
    double numerator;
    double denominator;
    double value;
    int idx;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    if (n == 0) {
        return 0;
    }
    std::vector<Fraction> fractions;
    for (int i = 0; i < n; i++) {
        double den, num;
        char del;
        std::cin >> num >> del >> den;
        fractions.push_back({num, den, num / den, i});
    }
    std::sort(fractions.begin(), fractions.end(), [](const Fraction& first, const Fraction& second) {
        if (first.value == second.value) {
            return first.idx < second.idx;
        }
        return first.value < second.value;
    });
    for (int i = 0; i < n; i++) {
        std::cout << fractions[i].numerator << '/' << fractions[i].denominator << ' ';
    }
    return 0;
}
