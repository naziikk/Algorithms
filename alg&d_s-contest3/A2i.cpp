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