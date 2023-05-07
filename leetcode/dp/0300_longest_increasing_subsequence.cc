#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
 public:
  // 贪心
  int static lengthOfLIS(vector<int> &nums) {
    int size = static_cast<int>(nums.size());
    vector<int> result(size, 1), sub{nums[0]};

    for (int i = 1; i < size; ++i) {
      if (nums[i] > sub[sub.size() - 1]) {
        sub.push_back(nums[i]);
      } else {
        *lower_bound(sub.begin(), sub.end(), nums[i]) = nums[i];
      }
    }
    return static_cast<int>(sub.size());
  }

  // 动态规划
  int static lengthOfLIS_DP(vector<int> &nums) {
    int size = static_cast<int>(nums.size());
    int max = 1;
    vector<int> result(size, 1);

    for (int i = 1; i < size; ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          result[i] = (result[i] < result[j] + 1) ? (result[j] + 1) : result[i];
          max = result[i] > max ? result[i] : max;
        }
      }
    }
    return max;
  }
};

int main() {
//  vector<int> vec{10, 9, 2, 5, 3, 7, 101, 18};
//  vector<int> vec{0,1,0,3,2,3};
  vector<int> vec{7,7,7,7,7,7,7};

  std::cout << Solution::lengthOfLIS(vec);
  return 0;
}