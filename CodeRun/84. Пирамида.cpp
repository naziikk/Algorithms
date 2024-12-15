#include <iostream>
#include <vector>
#include <unordered_map>

struct Block {
    int width;
    int height;
};

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> blocks;
    for (int i = 0; i < n; i++) {
        Block cur_block;
        std::cin >> cur_block.width >> cur_block.height;
        blocks[cur_block.width] = std::max(blocks[cur_block.width], cur_block.height);
    }
    long long ans = 0;
    for (const auto& [width, height] : blocks) {
        ans += height;
    }
    std::cout << ans;
    return 0;
}