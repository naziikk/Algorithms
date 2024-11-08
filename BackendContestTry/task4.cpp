#include <iostream>
#include <vector>

struct Order {
    int start_;
    int end_;
    int cost;

    Order(int start, int end, int cost) : start_(start), end_(end), cost(cost) {}
};

class FenwickTree {
    std::vector<int> arr_;

public:
    explicit FenwickTree(size_t size) : arr_(size + 1, 0) {}

    void Increment(int i, int delta) {
        for (; i < arr_.size(); i = (i | (i + 1))) {
            arr_[i] += delta;
        }
    }

    [[nodiscard]] int Sum(int r) const {
        int result = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            result += arr_[r];
        }
        return result;
    }

    [[nodiscard]] int Sum(int l, int r) const {
        return Sum(r) - Sum(l - 1);
    }

    void Init(const std::vector<Order>& orders) {
        for (size_t i = 0; i < orders.size(); i++) {
            Increment(i, orders[i].cost);
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Order> orders;
    for (int i = 0; i < n; i++) {
        int start, end, cost;
        std::cin >> start >> end >> cost;
        orders.emplace_back(start, end, cost);
    }

    FenwickTree fenwick(1e5 + 1);
    fenwick.Init(orders);
    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, type;
        std::cin >> l >> r >> type;
        if (type == 1) {
            std::cout << fenwick.Sum(l, r) << ' ';
        }
    }
    return 0;
}