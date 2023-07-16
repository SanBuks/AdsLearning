#include <vector>
#include <iostream>
using namespace std;
class Solution {
 public:
  int findPeakElement(vector<int> &nums) {
    int size = static_cast<int>(nums.size());
    if (size == 1) return 0;
    if (nums[0] > nums[1]) return 0;
    if (nums[size - 1] > nums[size - 2]) return size - 1;
    int lo = 1;
    int hi = size - 1;
    while (lo < hi) {
      int mi = lo + (hi - lo) / 2;
      if (nums[mi] < nums[mi - 1]) {
        hi = mi;
      } else if (nums[mi] < nums[mi + 1]) {
        lo = mi + 1;
      } else {
        return mi;
      }
    }
    return -1;
  }
};

int main() {
  Solution sol;
  vector<int> nums{1, 2, 1, 3, 5, 6, 4};
  std::cout << sol.findPeakElement(nums) << "\n";
  return 0;
}