#include <iostream>
#include <vector>
#include <unordered_map>

class FindLongestAnagram {
public:
    bool IsEqual(int len, int from1, int from2) {
        return (prefix_hash[from1 + len] - prefix_hash[from1])
               == (prefix_hash[from2 + len] - prefix_hash[from2])
               && (xor_prefix[from1 + len]  ^ xor_prefix[from1]) == (xor_prefix[from2 + len] ^ xor_prefix[from2]);
    }

    void compute_prefix_hash(int k) {
        prefix_hash.resize(k + 1);
        xor_prefix.resize(k + 1);
        for (int i = 1; i <= k; i++) {
            prefix_hash[i] = arr[i - 1] + prefix_hash[i - 1];
            xor_prefix[i] = arr[i - 1] ^ xor_prefix[i - 1];
        }
    }

    static void fillArray(int k, std::vector<int>& arr) {
        for (int i = 0; i < k; ++i) {
            int el;
            std::cin >> el;
            arr.push_back(el);
        }
    }

    int init() {
        std::cin >> n;
        fillArray(n, arr);
        std::cin >> m;
        fillArray(m, arr);
        compute_prefix_hash(n + m);
        size = std::min(n, m);
        return std::min(n, m);
    }

    std::pair<int, int> GetLongestAnagram(int h) {
        std::pair<int, int> result = {-1, -1};
        int len = 0;
        bool flag = false;
        for (int i = 0; i <= n - h; ++i) {
            for (int j = n; j <= n + m - h; ++j) {
                if (IsEqual(h, i, j)) {
                    if (h > len) {
                        result = {i + 1, j - n + 1};
                        len = h;
                        flag = true;
                        break;
                    }
                }
            }
            if (flag) {
                break;
            }
        }
        return result;
    }

private:
    int size;
    int n;
    int m;
    std::vector<int> arr;
    std::vector<long long> prefix_hash;
    std::vector<long long> xor_prefix;
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    FindLongestAnagram handler;
    int len = handler.init();
    int l = 0;
    int r = len;
    std::pair<int, int> ans = {-1, -1};
    int longest = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        std::pair<int, int> cur = handler.GetLongestAnagram(mid);
        if (cur.first != -1) {
            longest = mid;
            ans = cur;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    std::cout << longest << ' ' << ans.first << ' ' << ans.second;
    return 0;
}