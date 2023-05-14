#include <vector>
using namespace std;
class Solution {
  static const int mod_size = 1e9 + 7;
 public:
  int countGoodStrings(int low, int high, int zero, int one) {
    vector<int> dp(high + 1, 0); dp[0] = 1;
    int result = 0;

    int index;
    for (int i = 1; i <= high; ++i) {
      index = i - zero;
      if (index >= 0) {
        dp[i] = (dp[i] + dp[index]) % mod_size;
      }
      index = i - one;
      if (index >= 0) {
        dp[i] = (dp[i] + dp[index]) % mod_size;
      }
    }

    for (int i = low; i <= high; ++i) {
      result = (result + dp[i]) % mod_size;
    }
    return result;
  }
};