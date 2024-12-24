#include <iostream>
#include <vector>
#include <unordered_map>

struct Product {
    int product_id;
    int category_id;
};
int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> products;
    for (int i = 0; i < n; i++) {
        int product_id, category_id;
        std::cin >> product_id >> category_id;
        products[product_id] = category_id;
    }
    std::vector<Product> arrangement(n);
    for (int i = 0; i < n; i++) {
        int product_id;
        std::cin >> product_id;
        arrangement[i] = {product_id, products[product_id]};
    }
    products.clear();
    int ans = n;
    for (int i = 0; i < n; i++) {
        if (products.find(arrangement[i].category_id) != products.end()) {
            ans = std::min(ans, i - products[arrangement[i].category_id]);
        }
        products[arrangement[i].category_id] = i;
    }
    std::cout << ans;
    return 0;
}