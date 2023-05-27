#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

class Solution {
 public:
  static double new21Game(int n, int k, int maxPts) {
    vector<double> dp(n + 1, 0.0);
    dp[0] = 1.0;
    for (int i = 1; i <= n; ++i) {
      for (int j = max(i - maxPts, 0); j < i; ++j) {
        if (j > k)
        dp[i] += 1.0 / maxPts * dp[j];
      }
      for (const auto &item : dp) {
        cout << item << " ";
      }
      cout << "\n";
    }
    return accumulate(dp.begin() + k, dp.end(), 0.0);
  }
};

int main() {
  cout << Solution::new21Game(21, 17, 10) << "\n";
  return 0;
}