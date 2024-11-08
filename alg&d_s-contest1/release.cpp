#include <stdexcept>
#include "list.h"
#include <algorithm>
#include <unordered_map>

List::List() : head(nullptr), tail(nullptr), _size(0) {}

List::List(const List& other) : List() {
    copy(other);
}

List::List(std::vector<int> array) : List() {
    for (auto el : array) {
        push_back(el);
    }
}

List::~List() {
    clear();
}

int List::front() {
    if (_size != 0) {
        return head->value;
    }
}

int List::back() {
    if (_size != 0) {
        return tail->value;
    }
}

void List::push_back(int value) {
    Node* new_node = new Node(value);
    if (_size == 0) {
        head =  new_node;
        tail = new_node;
    }
    else {
        Node* prev = tail;
        tail->next = new_node;
        tail = tail->next;
        tail->prev = prev;

    }
    _size++;
}

void List::push_front(int value) {
    Node* new_node = new Node(value);
    if (_size == 0) {
        head =  new_node;
        tail = new_node;
    }
    else {
        Node* next_node = head;
        head->prev = new Node(nullptr, next_node, value);
        head = head->prev;
    }
    _size++;
}

void List::insert(Node* pos, int value) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }
    if (pos == tail) {
        push_back(value);
    }
    else {
        Node* new_node = new Node(value);
        new_node->next = pos->next;
        new_node->prev = pos;
        pos->next->prev = new_node;
        pos->next = new_node;
        _size++;
    }
}

void List::pop_front() {
    if (_size == 0) {
        throw std::runtime_error("Deleting in empty list");
    }
    Node *temp = head;
    if (head != tail) {
        head = head->next;
        head->prev = nullptr;
    }
    else {
        head = nullptr;
        tail = nullptr;
    }
    delete temp;
    _size--;
}
void List::pop_back() {
    if (_size == 0) {
        throw std::runtime_error("Deleting in empty list");
    }
    Node* temp = tail;
    if (tail != head) {
        tail = tail->prev;
        tail->next = nullptr;
    }
    else {
        head = nullptr;
        tail = nullptr;
    }
    delete temp;
    _size--;
}

void List::erase(Node* pos) {
    if (pos == nullptr) {
        throw std::runtime_error("Incorrect position!");
    }
    if (tail == pos) {
        pop_back();
    }
    else if (head == pos) {
        pop_front();
    }
    else {
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        delete pos;
        _size--;
    }
}

void List::clear() {
    while (_size != 0) {
        if (_size == 0) {
            throw std::runtime_error("Deleting in empty list");
        }
        Node *temp = head;
        if (head != tail) {
            head = head->next;
            head->prev = nullptr;
        }
        else {
            head = nullptr;
            tail = nullptr;
        }
        delete temp;
        _size--;
    }
}

void List::reverse() {
    if (_size == 0 || _size == 1) {
        return;
    }
    Node* cur = head;
    Node* temp = nullptr;
    while (cur) {
        temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }
    temp = head;
    head = tail;
    tail = temp;
}

void List::remove_duplicates() {
    if (_size <= 1) {
        return;
    }
    Node* cur = head;
    while (cur) {
        Node* noda = head;
        while (noda != cur) {
            if (noda->value == cur->value) {
                Node* temp = cur->next;
                erase(cur);
                cur = temp;
                break;
            }
            noda = noda->next;
        }
        if (noda == cur) {
            cur = cur->next;
        }
    }
}

void List::replace(int old_value, int new_value) {
    Node* cur = head;
    while (cur) {
        if (cur->value == old_value) {
            cur->value = new_value;
        }
        cur = cur->next;
    }
}

void List::merge(const List& other) {
    if (!other.head) {
        return;
    }
    Node* node = other.head;
    while (node) {
        push_back(node->value);
        node = node->next;
    }
}

bool List::check_cycle() const {
    if (_size == 0) {
        return false;
    }
    Node* fast = head;
    Node* slow = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

size_t List::size() const {
    return _size;
}

bool List::empty() const {
    return _size == 0;
}

void List::copy(const List& other) {
    clear();
    Node* cur = other.head;
    while (cur) {
        push_back(cur->value);
        cur = cur->next;
    }
}
