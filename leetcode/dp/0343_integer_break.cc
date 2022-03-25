#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /**
   * 2 <= n <= 58
   * 1 = 1 + 0 : 0
   * 2 = 1 + 1 : 1
   * 3 = 1 + 2 : 2
   * 4 = 2 + 2 : 4
   * 5 = 2 + 3 : 6
   */
  static int integerBreak(int n) {
    if (n == 2) {
      return 1;
    }
    if (n == 3) {
      return 2;
    }

    vector<int> dp(n + 1);
    dp[2] = 1;
    dp[3] = 2;
    for (int i = 4; i <= n; ++i) {
      int max = 0;
      for (int j = i - 2; j >= 2; --j) {
        if (dp[j] * dp[i - j] > max) {  // 拆分为 n + n 个数
          max = dp[j] * dp[i - j];
        }
        if (j * (i - j) > max) {        // 拆分为 2 数
          max = j * (i - j);
        }
        if (j * dp[i - j] > max) {      // 拆分为 1 + n 个数
          max = j * dp[i - j];
        }
      }
      dp[i] = max;
    }
    return dp[n];
  }
};

int main() {
  std::cout << Solution::integerBreak(2) << "\n";
  return 0;
}