#include <iostream>
#include <vector>
#include <iomanip>

struct Server {
    double requests;
    double mistake_percent;
    double mistake_count;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Server> servers(n);
    double sum = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> servers[i].requests >> servers[i].mistake_percent;
        servers[i].mistake_count = servers[i].requests / 100 * servers[i].mistake_percent;
        sum += servers[i].mistake_count;
    }
    for (int i = 0; i < n; i++) {
        std::cout << std::fixed << std::setprecision(10) << servers[i].mistake_count / sum << '\n';
    }
    return 0;
}