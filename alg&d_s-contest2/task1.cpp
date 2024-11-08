#include <iostream>
#include <vector>

struct Interval {
    int left_ = 0;
    int right_ = 0;

    Interval() = default;
    Interval(int left, int right) : left_(left), right_(right) {}

    Interval overlap(const Interval& other) {
        return Interval(std::max(left_, other.left_), std::min(right_, other.right_));
    }

    size_t length() const {
        return right_ - left_ + 1;
    }

    bool operator<(const Interval& other) {
        if (left_ != other.left_) {
            return left_ < other.left_;
        }
        return right_ > other.right_;
    }
};

void merge(std::vector<Interval>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<Interval> l(n1);
    std::vector<Interval> r(n2);
    for (int i = 0; i < n1; i++) {
        l[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        r[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (l[i] < r[j]) {
            arr[k] = l[i];
            i++;
        } else {
            arr[k] = r[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = l[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = r[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Interval>& arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

int main() {
    int n;
    std::cin >> n;
    if (n == 0) {
        std::cout << 0;
        return 0;
    }
    std::vector<Interval> arr(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;
        arr[i] = Interval(l, r);
    }
    mergeSort(arr, 0, n - 1);

    Interval ans;
    Interval temp = arr[0];
    size_t size = 0;
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i].left_ > temp.right_) {
            temp = arr[i];
        }
        else {
            Interval cur = temp.overlap(arr[i]);
            if (cur.length() > size) {
                ans = cur;
                size = cur.length();
            }
        }
        if (temp.right_ < arr[i].right_) {
            temp = arr[i];
        }
    }
    if (size == 0) {
        std::cout << 0;
        return 0;
    }
    std::cout << size << '\n';
    std::cout << ans.left_ << ' ' << ans.right_ << '\n';
    return 0;
}