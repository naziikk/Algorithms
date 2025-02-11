#include <iostream>
#include <vector>

template <class KeyType, class ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node *next;

    Node(KeyType key, ValueType value) : key(key), value(value), next(nullptr) {}
};

template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
    std::vector<Node<KeyType, ValueType>*> table;
    size_t size_;
    double load_factor_;
    Func hash_func;
    size_t elements_count;

    double load_factor() const {
        return static_cast<double>(elements_count) / size_;
    }

    void resizeAndRehash() {
        size_t new_size = size_ * 2;
        std::vector<Node<KeyType, ValueType>*> new_table(new_size, nullptr);
        for (size_t i = 0; i < size_; i++) {
            Node<KeyType, ValueType>* node = table[i];
            while (node != nullptr) {
                size_t hash = hash_func(node->key) % new_size;
                Node<KeyType, ValueType>* new_node = new Node<KeyType, ValueType>(node->key, node->value);
                new_node->next = new_table[hash];
                new_table[hash] = new_node;
                node = node->next;
            }
        }

        table = std::move(new_table);
        size_ = new_size;
    }

public:
    HashTable() : size_(100), load_factor_(0.5), elements_count(0) {
        table.resize(size_);
    }

    HashTable(Func func) : size_(100), load_factor_(0.5), hash_func(std::move(func)), elements_count(0) {
        table.resize(size_);
    }

    HashTable(size_t size, double load_factor, const Func& func = std::hash<KeyType>())
            : size_(size), hash_func(func), elements_count(0) {
        if (load_factor > 1 || load_factor <= 0) {
            load_factor_ = 0.5;
        } else {
            load_factor_ = load_factor;
        }
        table.resize(size_);
    }

    ~HashTable() {
        for (size_t i = 0; i < size_; i++) {
            Node<KeyType, ValueType>* node = table[i];
            while (node != nullptr) {
                Node<KeyType, ValueType>* next = node->next;
                delete node;
                node = next;
            }
        }
    }

    void insert(KeyType key, ValueType value) {
        size_t hash = hash_func(key) % size_;
        Node<KeyType, ValueType>* node = table[hash];

        while (node != nullptr) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            node = node->next;
        }

        node = new Node<KeyType, ValueType>(key, value);
        node->next = table[hash];
        table[hash] = node;
        elements_count++;

        if (load_factor() > load_factor_) {
            resizeAndRehash();
        }
    }

    ValueType* find(KeyType key) {
        size_t hash = hash_func(key) % size_;
        Node<KeyType, ValueType>* node = table[hash];
        while (node != nullptr) {
            if (node->key == key) {
                return &node->value;
            }
            node = node->next;
        }
        return nullptr;
    }

    void erase(KeyType key) {
        size_t hash = hash_func(key) % size_;
        Node<KeyType, ValueType>* node = table[hash];
        Node<KeyType, ValueType>* prev = nullptr;

        while (node != nullptr) {
            if (node->key == key) {
                if (prev) {
                    prev->next = node->next;
                } else {
                    table[hash] = node->next;
                }
                delete node;
                elements_count--;
                if (prev) {
                    delete prev;
                }
                return;
            }
            prev = node;
            node = node->next;
        }
    }

    Node<KeyType, ValueType>& operator[](size_t idx) {
        if (idx >= size_) {
            throw std::out_of_range("Индекс превышает размер массива");
        }
        Node<KeyType, ValueType>* node = table[idx];
        if (node == nullptr) {
            throw std::runtime_error("Ячейка пуста");
        }
        return *node;
    }

    Node<KeyType, ValueType>& at(size_t idx) {
        if (idx >= size_) {
            throw std::out_of_range("Индекс превышает размер массива");
        }
        auto& cell = table.at(idx);
        if (cell == nullptr) {
            throw std::runtime_error("Ячейка пуста");
        }
        return *cell;
    }

    int size() const {
        return elements_count;
    }

    int capacity() const {
        return size_;
    }
};