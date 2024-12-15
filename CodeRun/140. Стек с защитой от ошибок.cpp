#include <iostream>
#include <vector>

class Stack {
    std::vector<int> stack_;
    size_t size_ = 0;

public:
    void push(int n) {
        stack_.push_back(n);
        size_++;
    }

    int back() {
        return stack_.back();
    }

    int pop() {
        int last = back();
        stack_.pop_back();
        size_--;
        return last;
    }

    size_t size() const {
        return size_;
    }

    void clear() {
        stack_.clear();
        size_ = 0;
    }
};

int main() {
    Stack stack;
    std::string command;
    while (std::cin >> command) {
        if (command == "pop") {
            if (stack.size() == 0) {
                std::cout << "error\n";
            } else {
                std::cout << stack.pop() << '\n';
            }
        } else if (command == "push") {
            int num;
            std::cin >> num;
            stack.push(num);
            std::cout << "ok\n";
        } else if (command == "size") {
            std::cout << stack.size() << '\n';
        } else if (command == "back") {
            if (stack.size() == 0) {
                std::cout << "error\n";
            } else {
                std::cout << stack.back() << '\n';
            }
        } else if (command == "clear") {
            stack.clear();
            std::cout << "ok\n";
        } else {
            std::cout << "bye\n";
            break;
        }
    }
    return 0;
}