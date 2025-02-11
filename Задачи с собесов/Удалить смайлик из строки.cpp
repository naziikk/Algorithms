#include <iostream>
#include <vector>

void removeSmilesInPlace(std::string& s) {
    int l = 0;
    int r = 0;
    int n = s.length();
    while (r < n) {
        if (r + 2 < n && s[r] == ':' && s[r + 1] == '-' && s[r + 2] == ')') {
            r += 2;
            while (r < n && s[r] == ')') {
                r++;
            }
        } else {
            s[l] = s[r];
            r++;
            l++;
        }
    }
    s.resize(l);
}

int main() {

    return 0;
}