#include <vector>
using namespace std;
class Solution {
 public:
  int maxProfit(vector<int> &prices) {
    vector<pair<int, int>> dp(prices.size(), {0, 0});
    dp[0].first = -prices[0];  // keep
    dp[0].second = 0;          // no keep


    for (int i = 1; i < prices.size(); ++i) {
      dp[i].first = max(dp[i - 1].first, -prices[i]);
      dp[i].second = max(dp[i - 1].second, dp[i - 1].first + prices[i]);
    }

    return dp[prices.size() - 1].second;
  }
};