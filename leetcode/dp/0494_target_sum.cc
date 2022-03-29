#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  //1 <= nums.length <= 20
  //0 <= nums[i] <= 1000
  //0 <= sum(nums[i]) <= 1000
  //-1000 <= target <= 1000
  static int findTargetSumWays(vector<int> &nums, int target) {
    int sum = 0;
    for (const auto &item : nums) {
      sum += item;
    }

    if (target < -sum || sum < target) {
      return 0;
    }

    vector<int> dp(2 * sum + 1, 0);
    vector<int> dp_temp(2 * sum + 1, 0);

    int temp_a, temp_b;
    for (int i = 0; i < dp.size(); ++i) {
      temp_a = temp_b = 0;
      if (nums[0] == i - sum) {
        temp_a = 1;
      }
      if (-nums[0] == i - sum) {
        temp_b = 1;
      }
      dp[i] = temp_a + temp_b;
    }

    for (int i = 1; i < nums.size(); ++i) {
      for (int j = dp.size() - 1; j >= 0; --j) {
        temp_a = temp_b = 0;
        if (j - nums[i] >= 0) {
          temp_a = dp[j - nums[i]];
        }
        if (j + nums[i] < dp.size()) {
          temp_b = dp[j + nums[i]];
        }
        dp_temp[j] = temp_a + temp_b;
      }
      swap(dp, dp_temp);
    }

    return dp[target + sum];
  }
};

int main() {
  vector<int> vec{1,1,1,1,1};
  cout << Solution::findTargetSumWays(vec, 3) << "\n";
//  vector<int> vec{1};
//  cout << Solution::findTargetSumWays(vec, 1) << "\n";
  return 0;
}
