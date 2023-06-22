#include <vector>
using namespace std;
class Solution {
 public:
  int maxProfit(int k, vector<int> &prices) {
    vector<vector<int>> dp(prices.size(), vector<int> (2 * k, 0));

    // 偶持有 奇数不持有
    dp[0][0] = -prices[0];
    dp[0][2] = -prices[0];

    for (int i = 1; i < prices.size(); ++i) {



      dp[i][0] = max(dp[i - 1][0], -prices[i]);
      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);

      dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] - prices[i]);
      dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] + prices[i]);
    }

    return max(dp[prices.size() - 1][3], dp[prices.size() - 1][1]);
  }
};
