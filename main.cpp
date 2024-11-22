#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

class ArrayGenerator {
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib_size;
    std::uniform_int_distribution<> distrib_element;

public:
    ArrayGenerator(int from_size, int to_size, int from_element, int to_element)
        : gen(rd()), distrib_size(from_size / 100, to_size / 100), distrib_element(from_element, to_element) {}

    std::vector<int> generateRandomArray() {
        size_t size = distrib_size(gen) * 100;
        std::vector<int> nums(size);
        for (size_t i = 0; i < size; i++) {
            nums[i] = distrib_element(gen);
        }
        return nums;
    }

    std::vector<int> generateReversedArray() {
        std::vector<int> nums = generateRandomArray();
        std::sort(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.end());
        return nums;
    }

    std::vector<int> generateAlmostSortedArray() {
        std::vector<int> nums = generateReversedArray();
        size_t cnt_pairs_to_swap = distrib_element(gen) % 6;
        for (size_t i = 0; i < cnt_pairs_to_swap; i++) {
            size_t first_idx = distrib_element(gen) % nums.size();
            size_t second_idx = (distrib_element(gen) + 1) % nums.size();
            std::swap(nums[first_idx], nums[second_idx]);
        }
        return nums;
    }
};

int main() {
    ArrayGenerator gen(500, 10000, 0, 6000);
    std::vector<int> random_arr = gen.generateRandomArray();
    std::cout << "Случайный массив: размер - " << random_arr.size() << '\n';
    for (const auto& element : random_arr) {
        std::cout << element << ' ';
    }
    std::cout << '\n';

    std::vector<int> random_sorted_arr = gen.generateReversedArray();
    std::cout << "Случайный развернутый массив: размер - " << random_sorted_arr.size() << '\n';
    for (const auto& element : random_sorted_arr) {
        std::cout << element << ' ';
    }
    std::cout << '\n';

    std::vector<int> random_almost_sorted_arr = gen.generateAlmostSortedArray();
    std::cout << "Случайный почти отсортированный массив: размер - " << random_almost_sorted_arr.size() << '\n';
    for (const auto& element : random_almost_sorted_arr) {
        std::cout << element << ' ';
    }
    std::cout << '\n';

    return 0;
}