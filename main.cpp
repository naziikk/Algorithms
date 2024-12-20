#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

std::priority_queue<int> max_heap;
std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

void Insert(int num) {
    if (max_heap.empty() || num < max_heap.top()) {
        max_heap.push(num);
    } else {
        min_heap.push(num);
    }
    if (max_heap.size() > min_heap.size() + 1) {
        min_heap.push(max_heap.top());
        max_heap.pop();
    } else if (min_heap.size() > max_heap.size()) {
        max_heap.push(min_heap.top());
        min_heap.pop();
    }
}

int getMedian() {
    if (max_heap.size() >= min_heap.size()) {
        return max_heap.top();
    }
    return min_heap.top();
}

int main() {
    int n;
    std::cin >> n;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        Insert(num);
        sum += getMedian();
    }
    std::cout << sum;
    return 0;
}