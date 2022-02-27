#include <iostream>
#include <vector>

using namespace std;

/**
 * easy
 */
inline int abs(int x) {
  return x < 0 ? -x : x;
}

class Solution {
 public:
  vector<int> sortedSquares(vector<int> &nums) {
    size_t lo = 0, hi = nums.size() - 1, i = hi;
    vector<int> result(hi + 1);
    while (lo <= hi) {
      auto x = abs(nums[lo]);
      auto y = abs(nums[hi]);
      if (x >= y) {
        result[i--] = x * x;
        ++lo;
      } else {
        result[i--] = y * y;
        --hi;
      }
    }
    return result;
  }
};
