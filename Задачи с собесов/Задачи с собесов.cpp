#include <iostream>

std::string Convert(std::string& s) {
    int cnt_spaces = 0;
    for (const auto& symb : s) {
        if (std::isspace(symb)) {
            cnt_spaces++;
        }
    }
    int new_size = s.size() + 2 * cnt_spaces;
    int i = s.length() - 1;
    int j = new_size - 1;
    s.resize(new_size);
    while (i >= 0) {
        if (std::isspace(s[i])) {
            s[j] = '0';
            s[j - 1] = '2';
            s[j - 2] = '%';
            j -= 3;
        } else {
            s[j] = s[i];
            j--;
        }
        i--;
    }
    return s;
}