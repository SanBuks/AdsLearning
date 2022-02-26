#include <iostream>
#include <vector>

using namespace std;

/**
 *  easy 二分查找
 */
class Solution {
 public:
  /**
   * 准确版本
   */
  static int search(vector<int> &nums, int target) {
    int low = 0;
    // 1 <= nums.length <= 104
    int high = static_cast<int>(nums.size());
    while (low < high) {
      auto mid = low + (high - low) / 2;
      if (target == nums[mid]) {
        return mid;
      } else if (target < nums[mid]) {
        high = mid;
      } else {
        low = mid + 1;
      }
    }
    return -1;
  }

  /**
   * 查询靠左插入位置模板的修改版本
   */
  static int search2(vector<int> &nums, int target) {
    int max_num = static_cast<int>(nums.size());
    int lo = 0, hi = max_num;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (nums[mid] >= target) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    if (lo < nums.size() && nums[lo] == target) {
      return lo;
    } else if (lo < nums.size() && nums[lo] != target) {
      return -1;
    } else {
      return -1;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  vector<int> vec1{-1, 0, 3, 5, 9, 12};
  std::cout << Solution::search(vec1, 9) << "\n";
  return 0;
}
