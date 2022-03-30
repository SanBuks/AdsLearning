#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  static int coinChange(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 0; i < coins.size(); ++i) {
      for (int j = 1; j <= amount; ++j) {
        if (j - coins[i] >= 0 && dp[j - coins[i]] != INT_MAX) {
          dp[j] = min(dp[j], dp[j - coins[i]] + 1);
        }
      }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
  }
};

int main() {
//  vector<int> vec{1, 2, 5};
//  cout << Solution::coinChange(vec, 11) << "\n";
  vector<int> vec{2};
  cout << Solution::coinChange(vec, 3) << "\n";
  return 0;
}