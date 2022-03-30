#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  // 1 <= n <= 10^4
  static int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    vector<int> weight;
    for (int i = 1; i * i <= n; ++i) { weight.push_back(i * i); }

    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < weight.size(); ++j) {
        if (i - weight[j] >= 0 && dp[i - weight[j]] != INT_MAX) {
          dp[i] = min(dp[i], dp[i - weight[j]] + 1);
        }
      }
    }
    return dp[n];
  }
};

int main() {
  cout << Solution::numSquares(13) << "\n";
  return 0;
}