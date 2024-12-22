#include <iostream>
#include <vector>

struct node {
    node* next[26] = {};
    int count_prefixes = 0;
    std::string word;

    ~node() {
        for (int i = 0; i < 26; ++i) {
            delete next[i];
        }
    }
};

class Trie {
public:
    int Insert(const std::string& word) {
        node* current = root;
        int ans = -1;
        for (int i = 0; i < word.size(); i++) {
            int idx = word[i] - 'a';
            if (!current->next[idx]) {
                current->next[idx] = new node();
            }
            if (current->next[idx]->count_prefixes == 0) {
                current->next[idx]->word = word;
            } else if (current->next[idx]->count_prefixes == 1) {
                if (ans == -1 && word == current->next[idx]->word) {
                    ans = i + 1;
                    break;
                }
            }
            current->next[idx]->count_prefixes++;
            current = current->next[idx];
        }
        return ans == -1 ? word.length() : ans;
    }

private:
    node* root = new node();
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> words;
    std::string word;
    for (int i = 0; i < n; i++) {
        std::cin >> word;
        words.push_back(word);
    }
    long long ans = 0;
    Trie trie;
    for (const auto& current_word : words) {
        ans += (long long) trie.Insert(current_word);
    }
    std::cout << ans;
    return 0;
}