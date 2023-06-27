#include <vector>
#include <iostream>

using namespace std;
class Solution {
 public:
  int maxProfit(int k, vector<int> &prices) {
    vector<vector<int>> dp(prices.size(), vector<int> (2 * k, 0));

    // 偶持有 奇数不持有
    for (int i = 0; i < 2 * k; ++i) {
      dp[0][i] = !(i % 2) ? -prices[0] : 0;
    }

    for (int i = 1; i < prices.size(); ++i) {
      dp[i][0] = max(dp[i - 1][0], -prices[i]);
      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);

      for (int j = 2; j < 2 * k; ++j) {
        dp[i][j] = !(j % 2) ?
                   max(dp[i - 1][j], dp[i - 1][j - 1] - prices[i]) :
                   max(dp[i - 1][j], dp[i - 1][j - 1] + prices[i]);
      }
    }

    int ans = -1;
    for (int i = 1; i < 2 * k; i += 2) {
      ans = max(ans, dp[prices.size() - 1][i]);
    }
    return ans;
  }
};

int main() {
  Solution sol;
  vector<int> vec{3,2,6,5,0,3};
  cout << sol.maxProfit(2, vec) << "\n";
//  vector<int> vec{2, 4, 1};
//  cout << sol.maxProfit(2, vec) << "\n";
  return 0;
}
