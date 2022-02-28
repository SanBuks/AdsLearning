#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * mid
 */
class Solution {
 public:

  /**
   *  O(n) 滑动窗口
   */
  static int minSubArrayLen(int target, vector<int> &nums) {
    int result = INT_MAX;
    int sum = 0;
    size_t lo = 0;
    size_t hi = 0;
    while (true) {
      if (hi == nums.size() && sum < target) {
        break;
      }
      if (sum < target) {
        sum += nums[hi++];
      } else {
        sum -= nums[lo];
        ++lo;
      }
      if (sum >= target) {
        result = static_cast<int>(hi - lo < result ? hi - lo : result);
      }
    }
    return result == INT_MAX ? 0 : result;
  }

  static int binSearch(const vector<int> &vec, int lo, int hi, int target) {
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (vec[mid] > target) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    return --lo;
  }

  /**
   * O(nlogn) 累和 + 二分查找
   */
  static int minSubArrayLen2(int target, vector<int> &nums) {
    vector<int> acc(nums.size());
    int result = INT_MAX;
    const int size = static_cast<int>(nums.size());
    acc[0] = nums[0];

    // 累和 为了二分查找
    for (size_t i = 1; i != size; ++i) {
      acc[i] = acc[i - 1] + nums[i];
    }
    // acc[i] - target 为不必要的余量, 余量 = acc[0] + acc[1] + .. + acc[k]
    for (int i = size - 1; i >= 0 && acc[i] >= target; --i) {

      // upper_bound 返回第一个 > target 的位置
      auto k = upper_bound(acc.begin(), acc.begin() + i, acc[i] - target);
      auto num =  static_cast<int>(acc.begin() + i - (--k));
      result = (num < result ? num : result);

//      auto k = binSearch(acc, 0, i, acc[i] - target);
//      result = (i - k < result ? i - k : result);
    }
    return result == INT_MAX ? 0 : result;
  }
};

int main() {
  vector<int> vec{2,3,1,2,4,3};
  std::cout << Solution::minSubArrayLen2(7, vec);
  return 0;
}