#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
class Solution {
 public:
  int n;
  static const int MaxSum = 1000000;
  int dp[2][101][101];

  int Dfs(vector<int> &piles, int p, int i, int m) {
    if (i == n) {
      return 0;
    }

    int sum = 0;
    int result = p == 1 ? MaxSum : -1;
    int new_m = 0;
    for (int x = 1; x <= min(2 * m, n - i); ++x) {
      sum += piles[i + x - 1];
      new_m = max(x, m);

      if (p == 0) {
        if (dp[1][i + x][new_m] == -1)
          dp[1][i + x][new_m] = Dfs(piles, 1, i + x, new_m);
        result = max(result, sum + dp[1][i + x][new_m]);
      } else {
        if (dp[0][i + x][new_m] == -1)
          dp[0][i + x][new_m] = Dfs(piles, 0, i + x, new_m);
        result = min(result, dp[0][i + x][new_m]);
      }
    }
    return result;
  }

  int stoneGameII(vector<int> &piles) {
    memset(&dp, -1, sizeof(dp));
    n = static_cast<int>(piles.size());
    return Dfs(piles, 0, 0, 1);
  }
};
const int Solution::MaxSum;

int main() {
  Solution sol;
  vector<int> piles{2, 7, 9, 4, 4};
  cout << sol.stoneGameII(piles) << "\n";

  return 0;
}