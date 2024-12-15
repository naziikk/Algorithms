#include <iostream>
#include <vector>
#include <map>

int main() {
    std::map<std::string, std::map<std::string, long long>> customers_info;
    std::string last_name, item, amount;
    while (std::cin >> last_name && std::cin >> item && std::cin >> amount) {
        customers_info[last_name][item] += std::stol(amount);
    }
    for (const auto& [customer, items] : customers_info) {
        std::cout << customer << ":\n";
        for (const auto& [item_, amount_] : items) {
            std::cout << item_ << ' ' << amount_ << '\n';
        }
    }
    return 0;
}