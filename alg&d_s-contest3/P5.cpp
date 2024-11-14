#include <iostream>
#include <random>
#include <bitset>

std::vector<int> convertToBinary(std::string& s, int n) {
    std::vector<int> result;
    int bitCount = 0;
    for (char c : s) {
        int hexValue = std::stoi(std::string(1, c), nullptr, 16);
        std::bitset<4> binary(hexValue);
        for (int j = 3; j >= 0 && bitCount < n; --j) {
            result.push_back(binary[j]);
            bitCount++;
        }
    }
    while (result.size() < n) {
        result.push_back(0);
    }
    return result;
}

bool isEqualFreivalds(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B,
             std::vector<std::vector<int>>& C, std::vector<int>& arr, int n) {
    std::vector<int> Br(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Br[i] += (B[i][j] * arr[j]) % 2;
            Br[i] %= 2;
        }
    }
    std::vector<int> AB_r(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AB_r[i] += (A[i][j] * Br[j]) % 2;
            AB_r[i] %= 2;
        }
    }
    std::vector<int> C_r(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C_r[i] += (C[i][j] * arr[j]) % 2;
            C_r[i] %= 2;
        }
    }
    return AB_r == C_r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    std::vector<std::vector<int>> A(n, std::vector<int>(n));
    std::vector<std::vector<int>> B(n, std::vector<int>(n));
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    std::string current_row;
    for (int i = 0; i < n; i++) {
        std::cin >> current_row;
        A[i] = convertToBinary(current_row, n);
    }
    for (int i = 0; i < n; i++) {
        std::cin >> current_row;
        B[i] = convertToBinary(current_row, n);
    }
    for (int i = 0; i < n; i++) {
        std::cin >> current_row;
        C[i] = convertToBinary(current_row, n);
    }
    int m = 10;
    while (m--) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = distrib(gen);
        }
        if (!isEqualFreivalds(A, B, C, arr, n)) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}