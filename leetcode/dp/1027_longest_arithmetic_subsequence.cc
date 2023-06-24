#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
 public:
  int longestArithSeqLength(vector<int> &nums) {
    int size = static_cast<int>(nums.size());
    vector<vector<int>> dp(size, vector<int>(size));
    unordered_map<int, int> last_x_index;
    int res = -10000;

    for (int i = 0; i < size - 1; ++i) {
      for (int j = i + 1; j < size; ++j) {
        dp[i][j] = 2;
        int pre = nums[i] - (nums[j] - nums[i]);
        if (last_x_index.count(pre))
          dp[i][j] = dp[last_x_index[pre]][i] + 1;
        res = max(res, dp[i][j]);
      }
      last_x_index[nums[i]] = i;
    }
    return res;
  }
};

int main() {
  Solution sol;
  vector<int> vec{9, 4, 7, 2, 10};
  cout << sol.longestArithSeqLength(vec) << "\n";

  return 0;
}