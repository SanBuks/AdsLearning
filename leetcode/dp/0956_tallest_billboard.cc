#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
 public:
  int tallestBillboard(vector<int> &rods) {
    int sum = accumulate(rods.begin(), rods.end(), 0);
    vector<vector<int>> dp(rods.size() + 1, vector<int>(sum + 1, -1));

    dp[0][0] = 0;
    for (int i = 1; i <= rods.size(); ++i) {
      int h = rods[i - 1];
      for (int diff = 0; diff <= sum; ++diff) {
        if (dp[i - 1][diff] < 0) continue;
        dp[i][diff]          = max(dp[i][diff],          dp[i - 1][diff]);
        dp[i][diff + h]      = max(dp[i][diff + h],      dp[i - 1][diff]);
        dp[i][abs(diff - h)] = max(dp[i][abs(diff - h)], dp[i - 1][diff] + min(diff, h));
      }
    }
    return dp[rods.size()][0];
  }
};

int main() {
  Solution sol;
  vector<int> vec{1, 2, 3, 6};
  cout << sol.tallestBillboard(vec) << "\n";

  return 0;
}