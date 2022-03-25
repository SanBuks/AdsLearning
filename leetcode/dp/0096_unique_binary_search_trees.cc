#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /**
   * 1 <= n <= 19
   */
  static int numTrees(int n) {
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
      int sum = 0;
      for (int j = 1; j <= i; ++j) {
        int left = j - 1;
        int right = i - j;
        if (left == 0 || right == 0) {
          sum += left == 0 ? dp[right] : dp[left];
        } else {
          sum += dp[left] * dp[right];
        }
      }
      dp[i] = sum;
    }
    return dp[n];
  }
};

int main() {
  std::cout << Solution::numTrees(2) << "\n";
  return 0;
}
