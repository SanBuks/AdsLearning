#include <vector>

using namespace std;

/**
 *  easy
 */
class Solution {
 public:
  int static removeElement(vector<int> &nums, int val) {
    size_t i = 0;
    for (size_t j = 0; j != nums.size(); ++j) {
      if (nums[j] != val) {
        nums[i++] = nums[j];
      }
    }
    return i;
  }
};