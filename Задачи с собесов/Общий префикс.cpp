#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> commonPrefix(const std::vector<int>& first, const std::vector<int>& second) {
    int n = first.size();
    std::unordered_map<int, int> hash;
    std::vector<int> prefix(n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (hash.find(first[i]) != hash.end()) {
            if (hash[first[i]] == 1) {
                hash[first[i]] = 2;
                cnt++;
            }
        } else {
            hash[first[i]] = 0;
        }
        if (hash.find(second[i]) != hash.end()) {
            if (hash[second[i]] == 0) {
                hash[second[i]] = 2;
                cnt++;
            }
        } else {
            hash[second[i]] = 1;
        }
        prefix[i] = cnt;
    }
    return prefix;
}

int main() {
    std::vector<int> first = {1, 2, 2, 3, 4};
    std::vector<int> second = {1, 3, 2, 4, 2};
    std::vector<int> result = commonPrefix(first, second);
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << ' ';
    }
    return 0;
}