#include <iostream>
#include <vector>
#include <algorithm>

class HeapSort {
public:
    void heapify(std::vector<int>& arr, int i, int n) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l] > arr[largest]) {
            largest = l;
        }
        if (r < n && arr[r] > arr[largest]) {
            largest = r;
        }
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, largest, n);
        }
    }

    void buildMaxHeap(std::vector<int>& arr, int n) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, i, n);
        }
    }

    void heapSort(std::vector<int>& arr, int n) {
        buildMaxHeap(arr, n);
        for (int i = n - 1; i >= 0; i--) {
            std::swap(arr[i], arr[0]);
            heapify(arr, 0, i);
        }
    }
};

int main() {
    HeapSort heapsorter;
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    heapsorter.heapSort(nums, n);
    for (auto el : nums) {
        std::cout << el << ' ';
    }
    return 0;
}