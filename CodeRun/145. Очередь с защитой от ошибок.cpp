#include <stack>
#include <iostream>

class Queue {
public:
    void push(int num) {
        first.push(num);
    }

    int pop() {
        if (second.empty()) {
            while (!first.empty()) {
                second.push(first.top());
                first.pop();
            }
        }
        int val = second.top();
        second.pop();
        return val;
    }

    size_t size() {
        return first.size() + second.size();
    }

    int front() {
        if (second.empty()) {
            while (!first.empty()) {
                second.push(first.top());
                first.pop();
            }
        }
        int val = second.top();
        return val;
    }

    void clear() {
        while (!first.empty()) {
            first.pop();
        }
        while (!second.empty()) {
            second.pop();
        }
    }

private:
    std::stack<int> first;
    std::stack<int> second;
};

int main() {
    Queue queue;
    std::string command;
    while (std::cin >> command) {
        if (command == "pop") {
            if (queue.size() == 0) {
                std::cout << "error\n";
            } else {
                std::cout << queue.pop() << '\n';
            }
        } else if (command == "push") {
            int num;
            std::cin >> num;
            queue.push(num);
            std::cout << "ok\n";
        } else if (command == "size") {
            std::cout << queue.size() << '\n';
        } else if (command == "front") {
            if (queue.size() == 0) {
                std::cout << "error\n";
            } else {
                std::cout << queue.front() << '\n';
            }
        } else if (command == "clear") {
            queue.clear();
            std::cout << "ok\n";
        } else {
            std::cout << "bye\n";
            break;
        }
    }
    return 0;
}