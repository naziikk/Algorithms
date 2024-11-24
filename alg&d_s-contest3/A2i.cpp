#include <iostream>
#include <vector>
#include <algorithm>

static const int size = 15;

void merge(std::vector<int>& arr, int l, int mid, int r) {
    int n1 = mid - l + 1;
    int n2 = r - mid;
    std::vector<int> left_arr(n1);
    std::vector<int> right_arr(n2);
    for (int i = 0; i < n1; i++) {
        left_arr[i] = arr[i + l];
    }
    for (int i = 0; i < n2; i++) {
        right_arr[i] = arr[mid + i + 1];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (left_arr[i] < right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void insertionSort(std::vector<int>& arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int x = arr[i];
        int j = i;
        while (j > l && arr[j - 1] > x) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = x;
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (r - l <= size) {
        insertionSort(arr, l, r);
        return;
    }
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    mergeSort(arr, 0, n - 1);
    for (auto el : arr) {
        std::cout << el << ' ';
    }
    return 0;
}

//#include <iostream>
//#include <random>
//#include <vector>
//#include <algorithm>
//
//class ArrayGenerator {
//    std::random_device rd;
//    std::mt19937 gen;
//    std::uniform_int_distribution<> distrib_size;
//    std::uniform_int_distribution<> distrib_element;
//
//public:
//    ArrayGenerator(int from_size, int to_size, int from_element, int to_element)
//        : gen(rd()), distrib_size(from_size / 100, to_size / 100), distrib_element(from_element, to_element) {}
//
//    std::vector<int> generateRandomArray() {
//        size_t size = distrib_size(gen) * 100;
//        std::vector<int> nums(size);
//        for (size_t i = 0; i < size; i++) {
//            nums[i] = distrib_element(gen);
//        }
//        return nums;
//    }
//
//    std::vector<int> generateReversedArray() {
//        std::vector<int> nums = generateRandomArray();
//        std::sort(nums.begin(), nums.end());
//        std::reverse(nums.begin(), nums.end());
//        return nums;
//    }
//
//    std::vector<int> generateAlmostSortedArray() {
//        std::vector<int> nums = generateReversedArray();
//        size_t cnt_pairs_to_swap = distrib_element(gen) % 6;
//        for (size_t i = 0; i < cnt_pairs_to_swap; i++) {
//            size_t first_idx = distrib_element(gen) % nums.size();
//            size_t second_idx = (distrib_element(gen) + 1) % nums.size();
//            std::swap(nums[first_idx], nums[second_idx]);
//        }
//        return nums;
//    }
//};
//
//int main() {
//    ArrayGenerator gen(500, 10000, 0, 6000);
//    std::vector<int> random_arr = gen.generateRandomArray();
//    std::cout << "Случайный массив: размер - " << random_arr.size() << '\n';
//    for (const auto& element : random_arr) {
//        std::cout << element << ' ';
//    }
//    std::cout << '\n';
//
//    std::vector<int> random_sorted_arr = gen.generateReversedArray();
//    std::cout << "Случайный развернутый массив: размер - " << random_sorted_arr.size() << '\n';
//    for (const auto& element : random_sorted_arr) {
//        std::cout << element << ' ';
//    }
//    std::cout << '\n';
//
//    std::vector<int> random_almost_sorted_arr = gen.generateAlmostSortedArray();
//    std::cout << "Случайный почти отсортированный массив: размер - " << random_almost_sorted_arr.size() << '\n';
//    for (const auto& element : random_almost_sorted_arr) {
//        std::cout << element << ' ';
//    }
//    std::cout << '\n';
//
//    return 0;
//}