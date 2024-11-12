#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <numeric>

struct Fraction {
    double numerator;
    double denominator;
    double value;
    int idx;
};

void func(std::vector<Fraction>& fractions) {
    std::sort(fractions.begin(), fractions.end(), [](const Fraction& first, const Fraction& second) {
        if (first.value == second.value) {
            return first.idx < second.idx;
        }
        return first.value < second.value;
    });
    for (int i = 0; i < fractions.size(); i++) {
        std::cout << fractions[i].numerator << '/' << fractions[i].denominator << ' ';
    }
    std::cout << '\n';
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector< std::pair<long long, long long> >  fracs(n);
    std::vector<Fraction> fractions;
    for (int i = 0; i < n; ++i) {
        char c;
        std::cin >> fracs[i].first >> c >> fracs[i].second;
        fractions.push_back({(double) fracs[i].first, (double) fracs[i].second, (double) fracs[i].first / fracs[i].second, i});
    }
    func(fractions);
    long long lcm = 1;
    for (int i = 0; i < n; ++i) {
        lcm = (lcm / std::gcd(lcm, fracs[i].second)) * fracs[i].second;
    }
    std::vector< std::pair<long long, int> > numerators(n);
    for (int i = 0; i < n; ++i) {
        numerators[i].first = lcm / fracs[i].second * fracs[i].first;
        numerators[i].second = i;
    }
    std::sort(numerators.begin(), numerators.end(), [](std::pair<long long, int> a, std::pair<long long, int> b) {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });

    for (int i = 0; i < n; ++i) {
        std::cout << fracs[numerators[i].second].first << '/' << fracs[numerators[i].second].second << ' ';
    }
    return 0;
}

2
10000/1234 1234/10000