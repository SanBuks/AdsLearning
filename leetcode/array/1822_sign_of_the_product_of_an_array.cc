#include <vector>

using namespace std;

class Solution {
 public:
  int arraySign(vector<int> &nums) {
    if (nums[0] == 0) return 0;
    bool flag = nums[0] > 0;
    // - * + = -
    // - * - = +
    // + * + = +
    // + * - = -
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] == 0) return 0;
      if (nums[i] < 0 &&  flag) { flag = false; }
      else if (nums[i] < 0 && !flag) { flag = true; }
    }
    return flag ? 1 : -1;
  }
};