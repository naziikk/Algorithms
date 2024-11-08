#include <iostream>
#include <vector>
#include <iterator>

template <class Iterator, class Predicate>
void PartitionSort(Iterator begin, Iterator end, Predicate predicate) {
    while (begin != end) {
        while (predicate(*begin)) {
          ++begin;
          if (begin == end) {
              return;
          }
        } do {
          --end;
          if (begin == end) {
              return;
          }
        } while (!predicate(*end));
        std::swap(*begin, *end);
        ++begin;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums;
    for (int i = 0; i < n; i++) {
        int el;
        std::cin >> el;
        nums.push_back(el);
    }
    int bound;
    std::cin >> bound;
    PartitionSort(nums.begin(), nums.end(), [bound](int x) { return x < bound; });
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] < bound) {
            cnt++;
        } else {
            break;
        }
    }
    std::cout << cnt << '\n';
    std::cout << n - cnt;
    return 0;
}