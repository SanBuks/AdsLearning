#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
 public:
  int static maxProfit(vector<int> &prices) {
    vector<vector<int>> dp(prices.size(), {0, 0, 0, 0});

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

int main() {
  Solution sol;

//  vector<int> vec{3, 3, 5, 0, 0, 3, 1, 4};
  vector<int> vec{1, 2, 3, 4, 5};
  cout << sol.maxProfit(vec) << "\n";
  return 0;
}

//    for (const auto &row : dp) {
//      for (const auto &item : row) {
//        cout << item << " ";
//      }
//      cout << "\n";
//    }
