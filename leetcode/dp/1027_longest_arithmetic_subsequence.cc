#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
 public:
  int longestArithSeqLength2(vector<int> &nums) {
    int size = static_cast<int>(nums.size());
    // dp[i][j] 表示 以 nums[i] 为 左值, nums[j] 为右值, { ... , ..., nums[i], nums[j] } 序列的个数
    vector<vector<int>> dp(size, vector<int>(size));
    unordered_map<int, int> last_x_index;
    int res = -10000;

    // 以 i 为基准 遍历[i, j] 对, 同时记录左边 num[i] 出现的位置, 此时 num[j] 一定存在
    for (int i = 0; i < size - 1; ++i) {
      for (int j = i + 1; j < size; ++j) {
        // 找到前一个值
        int pre = nums[i] - (nums[j] - nums[i]);
        // 如果存在必在左侧, 必然与 i 构成同一序列
        if (last_x_index.count(pre)) {
          // last_x_index < i, 且 (last_x_index, i) 一定存在
          dp[i][j] = dp[last_x_index[pre]][i] + 1;
        } else {
          dp[i][j] = 2;
        }
        res = max(res, dp[i][j]);
      }
      // 更新记录
      last_x_index[nums[i]] = i;
    }
    return res;
  }

  int longestArithSeqLength(vector<int> &nums) {
    // dp[i] 存放以 nums[i] 为末元素的 delta 序列的长度, map 可以优化成 vector
    vector<unordered_map<int, int>> dp(nums.size());
    int ans = 1;
    for (int i = 1; i < nums.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        int delta = nums[i] - nums[j];
        if (dp[j].count(delta)) {
          dp[i][delta] = dp[j][delta] + 1;
        } else {
          dp[i][delta] = 2;
        }
        ans = max(ans, dp[i][delta]);
      }
    }
    return ans;
  }
};

int main() {
  Solution sol;
  vector<int> vec{9, 4, 7, 2, 10};
  cout << sol.longestArithSeqLength2(vec) << "\n";

  return 0;
}