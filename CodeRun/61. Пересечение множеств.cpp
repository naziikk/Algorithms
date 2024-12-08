#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
    std::string first;
    std::string second;
    std::getline(std::cin, first);
    std::getline(std::cin, second);
    std::vector<int> nums1;
    std::vector<int> nums2;
    std::istringstream iss1(first), iss2(second);
    int num;
    while (iss1 >> num) {
        nums1.push_back(num);
    }
    while (iss2 >> num) {
        nums2.push_back(num);
    }
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    int i = 0;
    int j = 0;
    std::vector<int> intersection;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] > nums2[j]) {
            j++;
        } else if (nums1[i] < nums2[j]) {
            i++;
        } else {
            intersection.push_back(nums1[i]);
            i++;
            j++;
        }
    }
    for (int i = 0; i < intersection.size(); i++) {
        std::cout << intersection[i] << ' ';
    }
    return 0;
}