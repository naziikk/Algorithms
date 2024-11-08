#include <iostream>
#include <vector>
#include <iterator>
#include <random>

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

void insertionSort(int l, int r, std::vector<int>& arr) {
    for (int i = l + 1; i <= r; i++) {
        int x = arr[i];
        int j = i;
        while (j > 0 && arr[j - 1] > x) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = x;
    }
}

const int M = 11;

void quickSort(int l, int r, std::vector<int>& arr) {
    if (r - l <= M) {
        insertionSort(l, r, arr);
        return;
    }
    int partition_point = PartitionSort(l, r + 1, arr);
    quickSort(l, partition_point - 1, arr);
    quickSort(partition_point + 1, r, arr);
}

int main() {
    std::freopen("/Users/nazarzakrevskij/CLionProjects/AlgoAndDS_hw1/input.txt", "r", stdin);
    int n;
    std::cin >> n;
    if (n == 0) {
        return 0;
    }
    std::vector<int> nums;
    for (int i = 0; i < n; i++) {
        int el;
        std::cin >> el;
        nums.push_back(el);
    }
    quickSort(0, n - 1, nums);
    for (int i = 0; i < n; i++) {
       std::cout << nums[i] << ' ';
    }
    return 0;
}