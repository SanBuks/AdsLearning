#include <vector>

using namespace std;

/**
 *  easy 二分查找
 *  返回插入 distinct array 的下标(重复元素之前)
 */
class Solution {
 public:
  static int searchInsert(vector<int> &nums, int target) {
    int low = 0;
    // 1 <= nums.length <= 104
    int high = static_cast<int>(nums.size());

    while (low < high) {
      auto mid = low + (high - low) / 2;
      if (nums[mid] < target) {
        low = mid + 1;  // [0, low) < target
      } else {
        high = mid;     // [high, size) >= target
      }
    }
    return low;
  }
};