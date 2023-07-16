#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
 public:
  int maxValue(vector<vector<int>> &events, int k) {
    const int size = static_cast<int>(events.size());
    sort(events.begin(), events.end(),
         [](const vector<int> &lvec, const vector<int> &rvec) { return lvec[1] < rvec[1]; });

    vector<vector<int>> dp(size + 1, vector<int>(k + 1, numeric_limits<int>::min()));
    for (int i = 0; i <= size; ++i) {
      dp[i][0] = 0;
    }

    int ans = 0;
    for (int i = 1; i <= size; ++i) {
      auto pos = upper_bound(events.begin(), events.begin() + i - 1, events[i][0] - 1,[](int value, const vector<int> &elem){
        return value < elem[1];
      });
      for (int j = 1; j <= k; ++j) {
        dp[i][j] = dp[i - 1][j];

        int delta = 0;
        if (pos != events.begin()) {
          delta = dp[distance(events.begin(), pos - 1) + 1][j - 1];
        }
        auto pick = delta + events[i][2];

        dp[i][j] = max(dp[i][j], pick);
        ans = max(ans, dp[i][j]);
      }
    }
    return ans;
  }
};

int main() {
  Solution sol;

  vector<vector<int>> vec{{1, 2, 4}, {3, 4, 3}, {2, 3, 10}};
  cout << sol.maxValue(vec, 2) << "\n";

  return 0;
}