#include <iostream>
#include <vector>

struct Data {
    long long pos;
    int count;
    long long rle_pos;

    bool operator<(int value) const {
        return pos < value;
    }
};

int main() {
    std::string s;
    std::cin >> s;
    std::vector<Data> ps;
    int n = s.length();
    long long prev = 0;
    long long prev_rle_pos = 0;
    ps.push_back({-1, 0, 0});
    for (int i = 0; i < n; i++) {
        if (std::isalpha(s[i])) {
            if (i < s.length() - 1 && !std::isdigit(s[i + 1])) {
                ps.push_back({prev + 1, 1, prev_rle_pos + 1});
                prev += 1;
                prev_rle_pos += 1;
            } else if (i == s.length() - 1) {
                ps.push_back({prev + 1, 1, prev_rle_pos + 1});
            } else {
                long long cnt = 0;
                int rem = i;
                i++;
                while (i < s.length() && std::isdigit(s[i])) {
                    cnt = cnt * 10 + (s[i] - '0');
                    i++;
                }
                i--;
                ps.push_back({prev + 1, static_cast<int>(cnt), prev_rle_pos + i - rem + 1});
                prev += cnt;
                prev_rle_pos += i - rem + 1;
            }
        }
    }
    for (int i = 0; i < ps.size(); i++) {
        std::cout << ps[i].pos << ' ' << ps[i].count << ' ' << ps[i].rle_pos << '\n';
    }
    std::cout << '\n';
    int requests;
    std::cin >> requests;
    for (int i = 0; i < requests; i++) {
        long long l, r;
        std::cin >> l >> r;
        auto left_idx = std::lower_bound(ps.begin(), ps.end(), l) - ps.begin();
        auto right_idx = std::lower_bound(ps.begin(), ps.end(), r) - ps.begin();
        int rem = 0;
        if (ps[left_idx].pos != l) {
            int dif = ps[left_idx - 1].pos + ps[left_idx - 1].count - l + 1;
            rem++;
            if (dif != 1) {
                for (const auto& symb : std::to_string(dif)) {
                    rem++;
                }
            }
            left_idx++;
        }
        if (ps[right_idx].pos != r) {
            int dif = ps[right_idx - 1].pos + ps[right_idx - 1].count - r + 1;
            rem++;
            if (dif != 1) {
                for (const auto& symb : std::to_string(dif)) {
                    rem++;
                }
            }
            right_idx--;
        }
        std::cout << left_idx << ' ' << right_idx << ' ' << rem << '\n';
        std::cout << std::max<long long>(0, ps[right_idx - 1].rle_pos - ps[left_idx - 1].rle_pos) + rem + 1 << '\n';
    }
    return 0;
}

//aabccca