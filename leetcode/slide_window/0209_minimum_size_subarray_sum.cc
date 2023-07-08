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
  // 1 <= target <= 10^9
  // 1 <= nums.length <= 10^5
  // 1 <= nums[i] <= 10^5
  static int minSubArrayLen(int target, vector<int> &nums) {
    int min_length = INT_MAX;
    int begin = 0;
    int sum = nums[0];
    if (sum >= target) {
      return 1;
    }
    for (int end = 1; end < nums.size(); ++end) {
      sum += nums[end];
      while (sum >= target) {
        min_length = min(min_length, end - begin + 1);
        sum -= nums[begin++];
      }
    }
    return min_length == INT_MAX ? 0 : min_length;
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

      // upper_bound 函数返回第一个 > target 的位置
      // --k 指向 <= 余量的位置
      // 目标区间为 (--k, begin() + i)]
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