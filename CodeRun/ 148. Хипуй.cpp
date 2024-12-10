#include <iostream>
#include <vector>

class Heap {
    std::vector<int> heap_;
    size_t size_ = 0;

    void buildMaxHeap(int index) {
        while (index > 0) {
            int parent_index = (index - 1) / 2;
            if (heap_[parent_index] >= heap_[index]) {
                break;
            }
            std::swap(heap_[parent_index], heap_[index]);
            index = parent_index;
        }
    }

    void heapify(int index) {
        while (2 * index + 1 < size_) {
            int left_child = 2 * index + 1;
            int right_child = 2 * index + 2;
            int largest_child = index;
            if (heap_[left_child] > heap_[largest_child]) {
                largest_child = left_child;
            }
            if (right_child < size_ && heap_[right_child] > heap_[largest_child]) {
                largest_child = right_child;
            }
            if (largest_child == index) {
                return;
            }
            std::swap(heap_[index], heap_[largest_child]);
            index = largest_child;
        }
    }

public:
    void Insert(int num) {
        heap_.push_back(num);
        size_++;
        buildMaxHeap(heap_.size() - 1);
    }

    int Extract() {
        int maxi = heap_[0];
        heap_[0] = heap_.back();
        heap_.pop_back();
        size_--;
        if (size_ > 0) {
            heapify(0);
        }
        return maxi;
    };
};

int main() {
    int n;
    std::cin >> n;
    Heap heap;
    for (int i = 0; i < n; i++) {
        int operation;
        std::cin >> operation;
        if (operation == 0) {
            int num;
            std::cin >> num;
            heap.Insert(num);
        } else {
            std::cout << heap.Extract() << '\n';
        }
    }
    return 0;
}
