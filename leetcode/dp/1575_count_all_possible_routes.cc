#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

const int mod = 1'000'000'000 + 7;

class Solution {
 public:
  int countRoutes(vector<int> &locations, int start, int finish, int fuel) {

    int size = static_cast<int>(locations.size());
    vector<vector<int>> dp(size, vector<int>(fuel + 1, 0));

    dp[start][fuel] = 1;

    for (int i = fuel - 1; i >= 0; --i) {
      for (int m = 0; m < size; ++m) {
        for (int n = 0; n < size; ++n) {
          if (n == m) continue;
          int delta = abs(locations[n] - locations[m]);
          dp[m][i] = i + delta > fuel ? dp[m][i] : (dp[m][i] + dp[n][i + delta]) % mod;
        }
      }
    }

    int sum = 0;
    for (int i = 0; i <= fuel; ++i) {
      sum = (sum + dp[finish][i]) % mod;

    }
    return sum;
  }
};

int main() {
  Solution sol;
  vector<int> vec{4,3,1};
  cout << sol.countRoutes(vec, 1, 0, 6) << "\n";
//  vector<int> vec{2, 3, 6, 8, 4};
//  cout << sol.countRoutes(vec, 1, 3, 5) << "\n";
  return 0;
}