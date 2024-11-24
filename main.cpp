#include <iostream>
#include <vector>
#include <cmath>
#include </Users/nazarzakrevskij/CLionProjects/AlgoAndDS_hw1/alg&d_s-contest3/A2i/ArrayGenerator.cpp>
const int M = 1000;

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

class InsertionSort {
public:
    void insertionSort(int l, int r, std::vector<int>& arr) {
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
};

class QuickSort {
    InsertionSort insertion;
    HeapSort heap;

public:
    int PartitionSort(int i, int j, std::vector<int>& arr) {
        int pivot = arr[j];
        int low = i - 1;
        for (int r = i; r < j; r++) {
            if (arr[r] < pivot) {
                low++;
                std::swap(arr[r], arr[low]);
            }
        }
        std::swap(arr[low + 1], arr[j]);
        return low + 1;
    }

    void quickSort(int l, int r, std::vector<int>& arr, int depth) {
        int maxDepth = 2 * std::log2(arr.size());
        if (depth >= maxDepth) {
            heap.heapSort(arr, r + 1);
            return;
        }

        if (r - l <= M) {
            insertion.insertionSort(l, r, arr);
            return;
        }
        if (r - l <= 1) {
            return;
        }
        int partition_point = PartitionSort(l, r, arr);
        quickSort(l, partition_point - 1, arr, depth + 1);
        quickSort(partition_point + 1, r, arr, depth + 1);
    }
};


int main() {
    QuickSort qsort;
   ArrayGenerator gen(10000, 10000, 0, 6000);
        // также можно вызвать любую другую функцию генерации массива
    std::vector<int> arr = gen.generateRandomArray();
    for (int i = 500; i <= 10000; i += 100) {
        int cur = 50;
        long long sum = 0;
        while (cur--) {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<int> array = {arr.begin(), arr.begin() + i};
            qsort.quickSort(0, array.size() - 1, array, 0); // вызов функции для обработки массива
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            sum += msec;
        }
        std::cout << sum / 50 << '\n';
    }
    return 0;
}