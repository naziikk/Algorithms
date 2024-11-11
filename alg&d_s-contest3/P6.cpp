#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

int correctQueens(const std::vector<int>& standing, int n) {
    int correctCount = 0;
    for (int i = 0; i < n; i++) {
        bool safe = true;
        for (int j = 0; j < n; j++) {
            if (i != j && (std::abs(i - j) == std::abs(standing[i] - standing[j]))) {
                safe = false;
                break;
            }
        }
        if (safe) {
            correctCount++;
        }
    }
    return correctCount;
}

std::vector<int> nQueens(int n) {
    std::vector<int> standing(n);
    for (int i = 0; i < n; i++) {
        standing[i] = i;
    }
    std::mt19937 gen(0);
    std::uniform_int_distribution<> distrib(0, 267);
    std::uniform_real_distribution<> dabli(0, 1);
    std::shuffle(standing.begin(), standing.end(), gen);
    int energy = correctQueens(standing, n);
    double temp = 1000;
    while (true) {
        temp *= 0.97;
        auto current_standing = standing;
        std::swap(current_standing[distrib(gen) % n], current_standing[(distrib(gen) % n + 1) % n]);
        int new_energy = correctQueens(current_standing, n);
        int dif = new_energy - energy;
        if (dif > 0 || dabli(gen) < std::exp(dif / temp)) {
            standing = current_standing;
            energy = new_energy;
        }
        if (new_energy == n) {
            break;
        }
    }
    return standing;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> ans = nQueens(n);
    for (auto el : ans) {
        std::cout << el + 1 << ' ';
    }
    return 0;
}