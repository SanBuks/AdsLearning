#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
 public:
  static pair<int, int> calc(const string &str) {
    int num_0 = 0, num_1 = 0;
    for (const auto &c : str) {
      if (c == '0') ++num_0;
      if (c == '1') ++num_1;
    }
    return {num_0, num_1};
  }

  static int findMaxForm(vector<string> &strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    auto status = calc(strs[0]);
    for (int i = 0; i <= m; ++i) {
      for (int j = 0; j <= n; ++j) {
        if (status.first <= i && status.second <= j) {
          dp[i][j] = 1;
        }
      }
    }

    for (int i_ = 1; i_ < strs.size(); ++i_) {
      status = calc(strs[i_]);
      for (int i = m; i >= status.first; --i) {
        for (int j = n; j >= status.second; --j) {
          dp[i][j] = max(dp[i][j], 1 + dp[i - status.first][j - status.second]);
        }
      }
    }

    return dp[m][n];
  }
};

int main() {
  vector<string> vec{"10", "0001", "111001", "1", "0"};
  cout << Solution::findMaxForm(vec, 5, 3) << " ";
//  vector<string> vec{"10", "0", "1"};
//  cout << Solution::findMaxForm(vec, 1, 1) << " ";

  return 0;
}