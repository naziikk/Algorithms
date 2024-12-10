#include <iostream>
#include <vector>

std::vector<int> merge(const std::vector<int>& first, const std::vector<int>& second, int l) {
    int i = 0;
    int j = 0;
    std::vector<int> ans;
    while (i < l && j < l) {
        if (first[i] < second[j]) {
            ans.push_back(first[i]);
            i++;
        } else {
            ans.push_back(second[j]);
            j++;
        }
    }
    while (i < l) {
        ans.push_back(first[i]);
        i++;
    }
    while (j < l) {
        ans.push_back(second[j]);
        j++;
    }
    return ans;
}

int main() {
    int n, l;
    std::cin >> n >> l;
    std::vector<std::vector<int>> sequences(n, std::vector<int>(l));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            std::cin >> sequences[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::vector<int> merge_array = merge(sequences[i], sequences[j], l);
            std::cout << merge_array[l - 1] << '\n';
        }
    }
    return 0;
}