#include <iostream>
#include <vector>

class HeapSort {
public:
    void heapify(std::vector<int>& arr, int n, int i) {
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        int largest = i;
        if (left_child < n && arr[left_child] > arr[i]) {
            largest = left_child;
        }
        if (right_child < n && arr[right_child] > arr[largest]) {
            largest = right_child;
        }
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void buildMaxHeap(int n, std::vector<int>& arr) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
    }

    void heapSort(std::vector<int>& arr, int n) {
        buildMaxHeap(n, arr);

        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    void print(const std::vector<int>& arr) {
        for (const auto& element : arr) {
            std::cout << element << ' ';
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    HeapSort heapSort;
    heapSort.heapSort(arr, n);
    heapSort.print(arr);
    return 0;
}