#include <iostream>
#include <vector>
#include <random>

class QuadraticProbing {
    std::vector<int> hash_table;
    size_t m;
    const int c1 = 1;
    const int c2 = 1;
    int tries = 0;
    int lucky_tries = 0;

public:
    QuadraticProbing(size_t m) : m(m) {
        hash_table.resize(m, -1);
    }

    void insert(int key) {
        size_t i = 0;
        size_t bin = key % m;
        int local_tries = 0;

        while (hash_table[bin] != -1 && i < m) {
            bin = (bin + c1 * i + c2 * i * i) % m;
            i++;
            local_tries++;
        }

        if (i < m) {
            hash_table[bin] = key;
            lucky_tries++;
            tries += local_tries + 1;
        }
    }

    size_t GetClustersCount() {
        size_t clusters = 0, current_size = 0;
        for (size_t i = 0; i < m; i++) {
            if (hash_table[i] == -1) {
                if (current_size > 0) {
                    clusters++;
                    current_size = 0;
                }
            } else {
                current_size++;
            }
        }
        return clusters + (current_size > 0 ? 1 : 0);
    }

    double GetAverageTries() {
        return lucky_tries > 0 ? (double) tries / lucky_tries : 0.0;
    }
};

class CubicProbing {
    std::vector<int> hash_table;
    size_t m;
    const int c1 = 1;
    const int c2 = 1;
    const int c3 = 1;
    int tries = 0;
    int lucky_tries = 0;

public:
    CubicProbing(size_t m) : m(m) {
        hash_table.resize(m, -1);
    }

    void insert(int key) {
        size_t i = 0;
        size_t bin = key % m;
        int local_tries = 0;

        while (hash_table[bin] != -1 && i < m) {
            bin = (bin + c1 * i + c2 * i * i + c3 * i * i * i) % m;
            i++;
            local_tries++;
        }

        if (i < m) {
            hash_table[bin] = key;
            lucky_tries++;
            tries += local_tries + 1;
        }
    }

    size_t GetClustersCount() {
        size_t clusters = 0, current_size = 0;
        for (size_t i = 0; i < m; i++) {
            if (hash_table[i] == -1) {
                if (current_size > 0) {
                    clusters++;
                    current_size = 0;
                }
            } else {
                current_size++;
            }
        }
        return clusters + (current_size > 0 ? 1 : 0);
    }

    double GetAverageTries() {
        return lucky_tries > 0 ? (double) tries / lucky_tries : 0.0;
    }
};

int main() {
    double weighted_clusters_quad = 0;
    double weighted_clusters_cubic = 0;
    double weighted_average_tries_quad = 0.0;
    double weighted_average_tries_cubic = 0.0;
    double total_weight = 0.0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(500, 10000);
    std::uniform_int_distribution<int> key_dist(1, 1000000);

    for (int j = 0; j < 100; j++) {
        int size = dist(gen);
        QuadraticProbing quadraticProbing(size);
        CubicProbing cubicProbing(size);

        int num_insertions = size / 2;

        for (int i = 0; i < num_insertions; i++) {
            int key = key_dist(gen);
            quadraticProbing.insert(key);
            cubicProbing.insert(key);
        }

        double weight = size;
        total_weight += weight;

        weighted_clusters_quad += quadraticProbing.GetClustersCount() * weight;
        weighted_clusters_cubic += cubicProbing.GetClustersCount() * weight;
        weighted_average_tries_quad += quadraticProbing.GetAverageTries() * weight;
        weighted_average_tries_cubic += cubicProbing.GetAverageTries() * weight;
    }

    std::cout << "Взвешенные средние показатели (учитывая размер таблиц):\n";
    std::cout << "Среднее количество кластеров (квадратичное пробирование): " << weighted_clusters_quad / total_weight << '\n';
    std::cout << "Среднее количество кластеров (кубическое пробирование): " << weighted_clusters_cubic / total_weight << '\n';
    std::cout << "Среднее количество попыток (квадратичное пробирование): " << weighted_average_tries_quad / total_weight << '\n';
    std::cout << "Среднее количество попыток (кубическое пробирование): " << weighted_average_tries_cubic / total_weight << '\n';

    return 0;
}