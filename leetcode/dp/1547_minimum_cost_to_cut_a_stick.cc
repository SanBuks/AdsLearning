#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
 public:
  int minCost(int n, vector<int> &cuts) {
    cuts.push_back(0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());

    int size = static_cast<int>(cuts.size());
    vector<vector<int>> dp(size, vector<int>(size, 0));

    for (int j = 2; j < size; ++j) {
      for (int i = 0; i < size - j; ++i) {
        int ii = i;
        int jj = j + i;

        int result = numeric_limits<int>::max();
        for (int k = ii + 1; k != jj; ++k) {
          int cost = dp[ii][k] + dp[k][jj];
          result = min(result, cost);
        }
        dp[ii][jj] = result + cuts[jj] - cuts[ii];
      }
//      print(dp);
    }

    return dp[0][size - 1];
  }
  void print(vector<vector<int>> &dp) {
    for (int i = 0; i < dp.size(); ++i) {
      for (int j = 0; j < dp.size(); ++j) {
        cout << dp[i][j] << " ";
      }
      cout << "\n";
    }
    cout << "------------------------------------\n";
  }
};

int main() {
  Solution sol;
  vector<int> nums{5, 6, 1, 4, 2};
  cout << sol.minCost(9, nums) << "\n";
  return 0;
}