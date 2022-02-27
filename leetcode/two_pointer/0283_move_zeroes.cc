#include <iostream>
#include <vector>

using namespace std;

/**
 * easy
 */
class Solution {
 public:
  void static moveZeroes(vector<int> &nums) {
    size_t i = 0;
    for (size_t j = 0; j < nums.size(); ++j) {
      if (nums[j] != 0) {
        nums[i++] = nums[j];
      }
    }
    for (size_t j = i; j < nums.size(); ++j) {
      nums[j] = 0;
    }
  }
};