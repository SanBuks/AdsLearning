#include <iostream>
#include <vector>

using namespace std;

/**
 *  easy 二分查找
 */
class Solution {
 public:
  static vector<int> searchRange(vector<int> &nums, int target) {
    int max = static_cast<int>(nums.size());
    int lo = 0, hi = max;
    vector<int> result{-1, -1};

    // 查找左边界
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (target <= nums[mid]) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    if (lo >= max || nums[lo] != target) {
      return result;
    } else {
      result[0] = lo;
    }

    // 查找右边界
    lo = lo + 1;
    hi = max;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (target < nums[mid]) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    --lo;
    if (lo < 0 || nums[lo] != target) {
      result[1] = -1;
    } else {
      result[1] = lo;
    }
    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
//  vector<int> vec{5, 7, 7, 8, 8, 10};
  vector<int> vec{1};
  auto result = Solution::searchRange(vec, 0);
  std::cout << result[0] << " " << result[1] << "\n";
  return 0;
}