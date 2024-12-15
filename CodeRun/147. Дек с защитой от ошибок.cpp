#include <iostream>
#include <stack>
#include <vector>

class Deque {
    std::vector<int> buffer;
    int front_idx = 0;
    int back_idx = 0;
    int capacity = 0;
    int count = 0;

public:
    Deque(int size = 10) : buffer(size), capacity(size) {}

    void push_front(int x) {
        if (count == capacity) {
            resize();
        }
        front_idx = (front_idx - 1 + capacity) % capacity;
        buffer[front_idx] = x;
        count++;
    }

    void push_back(int x) {
        if (count == capacity) {
            resize();
        }
        buffer[back_idx] = x;
        back_idx = (back_idx + 1) % capacity;
        count++;
    }

    int front() {
        return buffer[front_idx];
    }

    int back() {
        return buffer[(back_idx - 1 + capacity) % capacity];
    }

    int pop_front() {
        int val = buffer[front_idx];
        front_idx = (front_idx + 1) % capacity;
        count--;
        return val;
    }

    int pop_back() {
        back_idx = (back_idx - 1 + capacity) % capacity;
        count--;
        return buffer[back_idx];
    }

    void resize() {
        std::vector<int> new_buffer(capacity * 2);
        for (int i = 0; i < count; i++) {
            new_buffer[i] = buffer[(front_idx + i) % capacity];
        }
        buffer = std::move(new_buffer);
        front_idx = 0;
        back_idx = count;
        capacity *= 2;
    }

    size_t size() const {
        return count;
    }
    bool empty() const {
        return count == 0;
    }
    void clear() {
        front_idx = back_idx = count = 0;
    }
};

int main() {
    Deque deque;
    std::string command;
    while (std::cin >> command) {
        if (command == "pop_back") {
            if (deque.size() == 0) {
                std::cout << "error\n";
            } else {
                std::cout << deque.pop_back() << '\n';
            }
        } else if (command == "pop_front") {
            if (deque.size() == 0) {
                std::cout << "error\n";
            } else {
                std::cout << deque.pop_front() << '\n';
            }
        } else if (command == "push_back") {
            int num;
            std::cin >> num;
            deque.push_back(num);
            std::cout << "ok\n";
        } else if (command == "push_front") {
            int num;
            std::cin >> num;
            deque.push_front(num);
            std::cout << "ok\n";
        } else if (command == "size") {
            std::cout << deque.size() << '\n';
        } else if (command == "back") {
            if (deque.size() == 0) {
                std::cout << "error\n";
            } else {
                std::cout << deque.back() << '\n';
            }
        } else if (command == "front") {
            if (deque.size() == 0) {
                std::cout << "error\n";
            } else {
                std::cout << deque.front() << '\n';
            }
        } else if (command == "clear") {
            deque.clear();
            std::cout << "ok\n";
        } else {
            std::cout << "bye\n";
            break;
        }
    }
    return 0;
}