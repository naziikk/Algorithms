#include <iostream>
#include <unordered_map>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<std::string, int> langueges_freq;
    std::unordered_set<std::string> all_langueges;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int m;
        std::cin >> m;
        for (int j = 0; j < m; j++) {
            std::string lang;
            std::cin >> lang;
            all_langueges.insert(lang);
            langueges_freq[lang]++;
            if (langueges_freq[lang] == n) {
                cnt++;
            }
        }
    }
    std::cout << cnt << '\n';
    for (const std::string& lang : all_langueges) {
        if (langueges_freq[lang] == n) {
            std::cout << lang << '\n';
        }
    }
    std::cout << all_langueges.size() << '\n';
    for (const std::string& lang : all_langueges) {
        std::cout << lang << '\n';
    }
    return 0;
}