#include <iostream>
#include <vector>

void merge(int l, int mid, int r, std::vector<int>& arr) {
    int n1 = mid - l + 1;
    int n2 = r - mid;
    std::vector<int> left(n1);
    std::vector<int> right(n2);
    for (int i = 0; i < n1; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (left[i] < right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int l, int r, std::vector<int>& arr) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    mergeSort(l, mid, arr);
    mergeSort(mid + 1, r, arr);
    merge(l, mid, r, arr);
}

int main() {
    int k;
    std::cin >> k;
    std::vector<int> nums;
    for (int i = 0; i < k; i++) {
        int el;
        std::cin >> el;
        nums.push_back(el);
    }
    mergeSort(0, k - 1, nums);
    for (auto el : nums) {
        std::cout << el << ' ';
    }
    return 0;
}