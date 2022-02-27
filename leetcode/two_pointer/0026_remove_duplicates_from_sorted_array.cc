#include <iostream>
#include <vector>

using namespace std;

/**
 *  easy
 */
class Solution {
 public:
  int static removeDuplicates(vector<int> &nums) {
    if (nums.size() < 2) {
      return static_cast<int>(nums.size());
    }
    size_t i = 1;
    int target = nums[0];
    for (size_t j = 1; j < nums.size(); ++j) {
      if (nums[j] != target) {
        target = nums[j];
        nums[i++] = nums[j];
      }
    }
    return i;
  }
};