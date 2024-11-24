#include <iostream>
#include <vector>
#include </Users/nazarzakrevskij/CLionProjects/AlgoAndDS_hw1/alg&d_s-contest3/A2i/ArrayGenerator.cpp>

class SortTester {
public:
    static void testSort() {
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
    }

    void calculateWorkingTime() {
        ArrayGenerator gen(10000, 10000, 0, 6000);
        // также можно вызвать любую другую функцию генерации массива
        std::vector<int> arr = gen.generateAlmostSortedArray();
        for (int i = 500; i <= 10000; i += 100) {
            int cur = 50;
            long long sum = 0;
            while (cur--) {
                auto start = std::chrono::high_resolution_clock::now();
                std::vector<int> array = {arr.begin(), arr.begin() + i};
                mergeSort(array, 0, array.size() - 1); // вызов функции для обработки массива
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                sum += msec;
            }
            std::cout << sum / 50 << '\n';
        }
    }
};