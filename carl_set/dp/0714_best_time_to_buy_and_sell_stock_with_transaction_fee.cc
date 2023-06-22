#include <vector>
using namespace std;
class Solution {
 public:
  int maxProfit(vector<int> &prices, int fee) {
    vector<pair<int, int>> dp(prices.size(), {0, 0});
    dp[0].first = -prices[0];
    dp[0].second = 0;

    for (int i = 1; i < prices.size(); ++i) {
      dp[i].first = max(dp[i - 1].first, dp[i - 1].second - prices[i]);
      dp[i].second = max(dp[i - 1].second, dp[i - 1].first + prices[i] - fee);
    }
    return dp[prices.size() - 1].second;
  }
};