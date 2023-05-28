#include <vector>
#include <iostream>
using namespace std;
class Solution {
 public:
  int static findPeakElement(vector<int> &nums) {
    int size = static_cast<int>(nums.size());
    if (size == 1) {
      return 0;
    }

    if (nums[0] > nums[1]) {
      return 0;
    }
    if (nums[size - 1] > nums[size - 2]) {
      return size - 1;
    }

    bool find = false;
    size_t lo = 1, hi = size - 1, mid = 0;
    while (!find) {
      mid = lo + (hi - lo) / 2;
      if (nums[mid] < nums[mid - 1]) {
        hi = mid;
        continue;
      }
      if (nums[mid] < nums[mid + 1]) {
        lo = mid + 1;
        continue;
      }
      find = true;
    }
    return static_cast<int>(mid);
  }
};

int main() {
  vector<int> nums{1, 2, 1, 3, 5, 6, 4};

  std::cout << Solution::findPeakElement(nums) << "\n";
  return 0;
}