#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

struct Party {
    int votes;
    int bribe;
    int idx;
};

long long GetVotes(const std::vector<long long>& suffix_sums, int mean_votes, int i, const std::vector<Party>& parties) {
    int l = 0;
    int r = parties.size() - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (parties[mid].votes < mean_votes) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    long long votes = suffix_sums[l] - mean_votes * (parties.size() - l);
    if (parties[i].votes >= mean_votes) {
        votes -= (parties[i].votes - mean_votes);
    }
    return votes;
};

std::tuple<int, int, long> BinarySearch(const std::vector<Party>& parties, int idx, const std::vector<long long>& suffix_sums) {
    int l = 0;
    int r = 1e6;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        long long votes = GetVotes(suffix_sums, mid, idx, parties);
        if (parties[idx].votes + votes > mid) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    long long votes = GetVotes(suffix_sums, l, idx, parties);
    long long recovery = std::max<long long>(0, parties[idx].votes + votes - l - 2);
    std::tuple<int, int, long> result = {votes - recovery, l, recovery};
    return result;
}

int main() {
    long long n;
    std::cin >> n;
    std::vector<Party> parties(n);
    for (int i = 0; i < n; i++) {
        std::cin >> parties[i].votes >> parties[i].bribe;
        parties[i].idx = i;
    }
    std::sort(parties.begin(), parties.end(), [](const Party& first, const Party& second) {
        return first.votes < second.votes;
    });
    std::vector<long long> suffix_sums(n);
    suffix_sums[n - 1] = parties[n - 1].votes;
    for (int i = n - 2; i >= 0; i--) {
        suffix_sums[i] = parties[i].votes + suffix_sums[i + 1];
    }

    std::tuple<int, int, long> data;
    int idx = -1;
    long long min_cost = 1e10;
    for (int i = 0; i < n; i++) {
        if (parties[i].bribe != -1) {
            std::tuple<int, int, long> temp = BinarySearch(parties, i, suffix_sums);
            if (parties[i].bribe + std::get<0>(temp) < min_cost) {
                min_cost = parties[i].bribe + std::get<0>(temp);
                data = temp;
                idx = parties[i].idx;
            }
        }
    }
    std::vector<int> ans(n);
    long long cost = std::get<0>(data);
    int mean_value = std::get<1>(data);
    long long recovery = std::get<2>(data);
    for (int i = 0; i < n; i++) {
        if (parties[i].idx == idx) {
            ans[parties[i].idx] = parties[i].votes + cost;
        } else if (parties[i].votes <= mean_value) {
            ans[parties[i].idx] = parties[i].votes;
        } else {
            if (recovery > 0) {
                ans[parties[i].idx] = mean_value + 1;
                recovery--;
            } else {
                ans[parties[i].idx] = mean_value;
            }
        }
    }
    std::cout << min_cost << '\n';
    std::cout << idx + 1 << '\n';
    for (auto el : ans) {
        std::cout << el << ' ';
    }
    return 0;
}