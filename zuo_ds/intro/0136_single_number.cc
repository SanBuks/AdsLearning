#include <vector>
#include <iostream>
using namespace std;
class Solution {
 public:
  int singleNumber(vector<int> &nums) {
    auto item = nums[0];
    for (size_t i = 1; i != nums.size(); ++i) {
      item ^= nums[i];
    }
    return item;
  }
};