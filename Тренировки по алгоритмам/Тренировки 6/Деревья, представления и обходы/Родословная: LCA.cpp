#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

std::string LCA(std::unordered_map<std::string, std::string>& dct, std::string& s, std::string& t) {
    std::unordered_set<std::string> st;
    st.insert(s);
    std::string first = s;
    while (dct.find(first) != dct.end()) {
        first = dct[first];
        st.insert(first);
    }
    std::string second = t;
    if (st.find(second) != st.end()) {
        return second;
    }
    while (dct.find(second) != dct.end()) {
        second = dct[second];
        if (st.find(second) != st.end()) {
            return second;
        }
    }
    return "";
}

int main() {
   int n;
    std::cin >> n;
    std::unordered_map<std::string, std::string> dct;
    std::unordered_set<std::string> children;
    for (int i = 0; i < n - 1; ++i) {
        std::string child, parent;
        std::cin >> child >> parent;
        dct[child] = parent;
        children.insert(child);
    }
    std::string first, second;
    while (std::cin >> first && std::cin >> second) {
        std::cout << LCA(dct, first, second) << '\n';
    }
    return 0;
}