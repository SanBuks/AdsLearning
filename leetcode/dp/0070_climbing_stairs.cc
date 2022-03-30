#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  static int climbStairs(int n) {
    int pre = 1;
    int now = 2;

    if (n == 1) {
      return pre;
    }
    if (n == 2) {
      return now;
    }

    int sum = 0;

    for (int i = 3; i <= n; ++i) {
      sum = pre + now;
      pre = now;
      now = sum;
    }
    return sum;
  }

  static int climbStairs_complete_bag(int n) {
    vector<int> dp(n + 1, 0);

    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= 2; ++j) {
        if (i - j >= 0) {
          dp[i] += dp[i - j];
        }
      }
    }
    return dp[n];
  }
};

int main () {
  std::cout << Solution::climbStairs(4) << "\n";
  return 0;
}