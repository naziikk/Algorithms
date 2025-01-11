#include <iostream>
#include <vector>

const int mod = 1e9 + 7;
const int base = 257;
std::vector<long long> power_of_base;

void precomputePowerOfBase(int max_length) {
    power_of_base.resize(max_length + 1, 1);
    for (int i = 1; i <= max_length; i++) {
        power_of_base[i] = (power_of_base[i - 1] * base) % mod;
    }
}

std::vector<long long> hashWord(const std::string& word) {
    int n = word.size();
    std::vector<long long> hash(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] * base + (word[i - 1] - 'a' + 1)) % mod;
    }
    return hash;
}

bool Hash(int len, int from1, int from2, const std::vector<long long>& hash1, const std::vector<long long>& hash2) {
    long long h1 = (hash1[from1 + len] - hash1[from1] * power_of_base[len] % mod + mod) % mod;
    long long h2 = (hash2[from2 + len] - hash2[from2] * power_of_base[len] % mod + mod) % mod;
    return h1 == h2;
}

class Solution {
public:
    int countPrefixSuffixPairs(std::vector<std::string>& words) {
        int n = words.size();
        int longest = 0;
        for (const auto& word : words) {
            longest = std::max(longest, (int)word.size());
        }
        precomputePowerOfBase(longest);

        std::vector<std::vector<long long>> hashes(n);
        for (int i = 0; i < n; i++) {
            hashes[i] = hashWord(words[i]);
        }

        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int len = words[i].size();
                if (len <= words[j].size() &&
                    Hash(len, 0, 0, hashes[i], hashes[j]) &&
                    Hash(len, words[i].size() - len, words[j].size() - len, hashes[i], hashes[j])) {
                    count++;
                }
            }
        }
        return count;
    }
};