#include <iostream>
#include <vector>
#include <cmath>

const int M = 16;

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
        int partition_point = PartitionSort(l, r, arr);
        quickSort(l, partition_point - 1, arr, depth + 1);
        quickSort(partition_point + 1, r, arr, depth + 1);
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    QuickSort quicksort;
    quicksort.quickSort(0, n - 1, arr, 0);
    for (auto el : arr) {
        std::cout << el << ' ';
    }
    return 0;
}