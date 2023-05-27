#include <vector>
#include <iostream>
#include <cstring>
#include <numeric>

using namespace std;
class Solution {
 public:
  int size;
  int dp[2][501][501];
  enum Player { Alice = 0, Bob };

  bool stoneGame(vector<int> &piles) {
    size = static_cast<int>(piles.size());
    memset(dp, -1, sizeof(dp));

    int sum = accumulate(piles.cbegin(), piles.cend(), 0);
    int alice = Dfs(piles, Alice, 0, size);
    return alice > sum - alice;
  }

  int Dfs(vector<int> &piles, int player, int low, int high) {
    if (low == high) { return 0; }
    int result = (player == Alice ? -1 : 250001);
    if (player == Alice) {
      if (dp[Bob][low + 1][high] == -1) {
        dp[Bob][low + 1][high] = Dfs(piles, Bob, low + 1, high);
      }
      result = max(result, piles[low] + dp[Bob][low + 1][high]);

      if (dp[Bob][low][high - 1] == -1) {
        dp[Bob][low][high - 1] = Dfs(piles, Bob, low, high - 1);
      }
      result = max(result, piles[high - 1] + dp[Bob][low][high - 1]);
    } else {
      if (dp[Alice][low + 1][high] == -1) {
        dp[Alice][low + 1][high] = Dfs(piles, Alice, low + 1, high);
      }
      result = min(result, dp[Alice][low + 1][high]);

      if (dp[Alice][low][high - 1] == -1) {
        dp[Alice][low][high - 1] = Dfs(piles, Alice, low, high - 1);
      }
      result = min(result, dp[Alice][low][high - 1]);
    }
    return result;
  }
};