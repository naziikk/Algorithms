#include <iostream>
#include <vector>

int findLeftMedian(const std::vector<int>& seq1, const std::vector<int>& seq2, int L) {
    int i = 0, j = 0;
    int count = 0;
    int leftMedian = 0;
    while (count < L) {
        if (i < L && (j >= L || seq1[i] <= seq2[j])) {
            leftMedian = seq1[i];
            i++;
        } else {
            leftMedian = seq2[j];
            j++;
        }
        count++;
    }
    return leftMedian;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, l;
    std::cin >> n >> l;
    std::vector<std::vector<int>> sequences(n, std::vector<int>(l));
    for (int i = 0; i < n; i++) {
        int x, d, a, c, m;
        std::cin >> x >> d >> a >> c >> m;
        sequences[i][0] = x;
        for (int j = 1; j < l; j++) {
            sequences[i][j] = sequences[i][j - 1] + d;
            d = d * a + c;
            d %= m;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int median = findLeftMedian(sequences[i], sequences[j], l);
            std::cout << median << '\n';
        }
    }
    return 0;
}