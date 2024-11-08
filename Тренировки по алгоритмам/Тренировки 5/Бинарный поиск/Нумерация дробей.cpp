#include <iostream>
#include <vector>

int main() {
    long long n;
    std::cin >> n;
    long long l = 0;
    long long r = n + 1;
    while (l <= r) {
        long long mid = (l + r) / 2;
        if (mid * (mid + 1) / 2 >= n) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    long long diagonal = l;
    long long position = n - (l - 1) * l / 2;
    if (diagonal % 2 == 1) {
        std::cout << position << '/' << diagonal - position + 1;
    } else {
        std::cout << diagonal - position + 1 << '/' << position;
    }
    return 0;
}