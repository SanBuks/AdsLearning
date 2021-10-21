#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> result;
    if (nums.size() < 3) {
      return {};
    }

    std::sort(nums.begin(), nums.end());

    size_t left = 0;
    size_t right = nums.size() - 1;
    if (nums[left] > 0 || nums[right] < 0 || nums[left] == nums[right]) {
      return result;
    }

    return result;
  }

};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<int> vec{-1, 0, 1, 2, -1, -4};
  Solution solution;
  auto v = solution.threeSum(vec);
  for (auto i: v) {
    for (auto j: i) {
      std::cout << j << " ";
    }
    std::cout << "\n";
  }
}