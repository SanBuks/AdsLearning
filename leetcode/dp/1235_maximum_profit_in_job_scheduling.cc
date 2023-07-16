#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
    const int size = static_cast<int>(startTime.size());
    vector<vector<int>> data(size, vector<int>(3, 0));
    for (int i = 0; i < size; ++i) {
      data[i][0] = startTime[i];
      data[i][1] = endTime[i];
      data[i][2] = profit[i];
    }
    // 求 规划区间权重之和最大 按照 end 排序
    // dp[i] 表示 前 i 个区间中 最大权重之和
    sort(data.begin(), data.end(), [](const vector<int> &lvec, const vector<int> &rvec) { return lvec[1] < rvec[1]; });

    vector<int> dp(size + 1);
    dp[0] = data[0][2];

    int ans = dp[0];
    for (int i = 1; i < size; ++i) {
      auto not_pick = dp[i - 1];

      // 找到最先出现的相交的区间
      auto pos = upper_bound(data.begin(), data.begin() + i, data[i][0], [](int value, const vector<int> &elem) {
        return value < elem[1];
      });
      int delta = 0;
      // 存在不相交区域
      if (pos != data.begin()) {
        delta = dp[distance(data.begin(), pos - 1)];
      }
      auto pick = delta + data[i][2];

      dp[i] = max(not_pick, pick);
      ans = max(ans, dp[i]);
    }
    return ans;
  }
};


int main() {
  Solution sol;

  vector<int> startTime = {1, 2, 3, 4, 6};
  vector<int> endTime = {3, 5, 10, 6, 9};
  vector<int> profit = {20, 20, 100, 70, 60};
  cout << sol.jobScheduling(startTime, endTime, profit) << "\n";

  return 0;
}