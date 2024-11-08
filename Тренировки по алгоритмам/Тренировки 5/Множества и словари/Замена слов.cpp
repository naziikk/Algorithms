#include <iostream>
#include <sstream>

struct Node {
    Node* next[26] = {};
    bool end = false;
};

class Trie {
    Node* root = new Node();

public:
    void Insert(const std::string& s) {
        Node* cur = root;
        for (int i = 0; i < s.length(); i++) {
            if (cur->next[s[i] - 'a'] == nullptr) {
                cur->next[s[i] - 'a'] = new Node();
            }
            cur = cur->next[s[i] - 'a'];
        }
        cur->end = true;
    }

    std::string Find(const std::string& s) {
         Node* cur = root;
         std::string temp;
        for (int i = 0; i < s.length(); i++) {
            temp += s[i];
            if (cur->next[s[i] - 'a'] == nullptr) {
                return "";
            }
            cur = cur->next[s[i] - 'a'];
            if (cur->end == true) {
                return temp;
            }
        }
        return "";
    }
};
int main() {
    Trie trie;
    std::string a, b;
    std::getline(std::cin, a);
    std::istringstream f_stream(a);
    std::string word;
    while (f_stream >> word) {
        trie.Insert(word);
    }
    std::getline(std::cin, b);
    std::istringstream s_stream(b);
    std::string result;
    while (s_stream >> word) {
        std::string cur = trie.Find(word);
        if (cur.empty()) {
            result += word + ' ';
        } else {
            result += cur + ' ';
        }
    }
    std:: cout << result;
    return 0;
}