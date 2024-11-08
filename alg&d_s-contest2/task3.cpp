#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>


std::vector<std::vector<long long>> summation(const std::vector<std::vector<long long>>& a, const std::vector<std::vector<long long>>& b) {
    size_t n = a.size();
    size_t m = a[0].size();
    std::vector<std::vector<long long>> result(n, std::vector<long long>(m, 0));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            result[i][j] = a[i][j] + b[i][j];

    return result;
}

std::vector<std::vector<long long>> subtraction(const std::vector<std::vector<long long>>& a, const std::vector<std::vector<long long>>& b) {
    size_t n = a.size();
    size_t m = a[0].size();
    std::vector<std::vector<long long>> result(n, std::vector<long long>(m, 0));

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            result[i][j] = a[i][j] - b[i][j];

    return result;
}

void splitMatrix(const std::vector<std::vector<long long>>& a, std::vector<std::vector<long long>>& a11, std::vector<std::vector<long long>>& a12, std::vector<std::vector<long long>>& a21, std::vector<std::vector<long long>>& a22) {
    size_t n = a.size();
    size_t mid = n / 2;

    a11.assign(mid, std::vector<long long>(mid, 0));
    a12.assign(mid, std::vector<long long>(mid, 0));
    a21.assign(mid, std::vector<long long>(mid, 0));
    a22.assign(mid, std::vector<long long>(mid, 0));

    for (size_t i = 0; i < mid; ++i) {
        for (size_t j = 0; j < mid; ++j) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + mid];
            a21[i][j] = a[i + mid][j];
            a22[i][j] = a[i + mid][j + mid];
        }
    }
}

std::vector<std::vector<long long>> collectMatrix(const std::vector<std::vector<long long>>& c11, const std::vector<std::vector<long long>>& c12, const std::vector<std::vector<long long>>& c21, const std::vector<std::vector<long long>>& c22) {
    size_t mid = c11.size();
    size_t n = mid * 2;
    std::vector<std::vector<long long>> c(n, std::vector<long long>(n, 0));

    for (size_t i = 0; i < mid; ++i) {
        for (size_t j = 0; j < mid; ++j) {
            c[i][j] = c11[i][j];
            c[i][j + mid] = c12[i][j];
            c[i + mid][j] = c21[i][j];
            c[i + mid][j + mid] = c22[i][j];
        }
    }

    return c;
}
std::vector<std::vector<long long>> naiveMultiply(const std::vector<std::vector<long long>>& a, const std::vector<std::vector<long long>>& b, int n) {
    std::vector<std::vector<long long>> ans(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ans[i][k] += a[i][j] * b[j][k];
            }
        }
    }
    return ans;
}

std::vector<std::vector<long long>> multiStrassen(const std::vector<std::vector<long long>>& a, const std::vector<std::vector<long long>>& b, int n) {
    if (n <= 128) {
        return naiveMultiply(a, b, n);
    }
    int newSize = n / 2;

    std::vector<std::vector<long long>> a11, a12, a21, a22;
    std::vector<std::vector<long long>> b11, b12, b21, b22;

    splitMatrix(a, a11, a12, a21, a22);
    splitMatrix(b, b11, b12, b21, b22);
    std::vector<std::vector<long long>> p1 = multiStrassen(summation(a11, a22), summation(b11, b22), newSize);
    std::vector<std::vector<long long>> p2 = multiStrassen(summation(a21, a22), b11, newSize);
    std::vector<std::vector<long long>> p3 = multiStrassen(a11, subtraction(b12, b22), newSize);
    std::vector<std::vector<long long>> p4 = multiStrassen(a22, subtraction(b21, b11), newSize);
    std::vector<std::vector<long long>> p5 = multiStrassen(summation(a11, a12), b22, newSize);
    std::vector<std::vector<long long>> p6 = multiStrassen(subtraction(a21, a11), summation(b11, b12), newSize);
    std::vector<std::vector<long long>> p7 = multiStrassen(subtraction(a12, a22), summation(b21, b22), newSize);
    std::vector<std::vector<long long>> c11 = summation(subtraction(summation(p1, p4), p5), p7);
    std::vector<std::vector<long long>> c12 = summation(p3, p5);
    std::vector<std::vector<long long>> c21 = summation(p2, p4);
    std::vector<std::vector<long long>> c22 = summation(subtraction(p1, p2), summation(p3, p6));
    return collectMatrix(c11, c12, c21, c22);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<std::vector<long long>> mat1(n, std::vector<long long>(n, 0));
    std::vector<std::vector<long long>> mat2(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num;
            std::cin >> num;
            mat1[i][j] = num;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num;
            std::cin >> num;
            mat2[i][j] = num;
        }
    }
    std::vector<std::vector<long long>> ans = multiStrassen(mat1, mat2, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << ans[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}