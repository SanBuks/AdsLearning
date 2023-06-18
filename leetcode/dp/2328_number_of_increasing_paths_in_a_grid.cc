#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

const int mod = 1'000'000'000 + 7;
int row, col;
class Solution {
 public:
  int countPaths(vector<vector<int>> &grid) {
    row = static_cast<int>(grid.size());
    col = static_cast<int>(grid[0].size());

    vector<vector<pair<int, int>>> dp(row, vector<pair<int, int>>(col, {0, 1}));

    int sum = 0;
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        sum = (sum + dfs(i, j, grid, dp)) % mod;
      }
    }
    return sum;
  }

  int dfs(int i, int j, vector<vector<int>> &grid, vector<vector<pair<int, int>>> &dp) {
    if (dp[i][j].first != 0) {
      return dp[i][j].second;
    }

    int sum = dp[i][j].second;

    int arr[5] = {1, 0, -1, 0, 1};

    for (int k = 0; k < 4; ++k) {
      int r = arr[k] + i;
      int c = arr[k + 1] + j;

      if (r >= 0 && r < row && c >= 0 && c < col && grid[i][j] < grid[r][c]) {
        sum = (sum + dfs(r, c, grid, dp)) % mod;
      }
    }
    dp[i][j].first = 1;
    dp[i][j].second = sum;
    return dp[i][j].second;
  }
};


int main() {
  Solution sol;
  vector<vector<int>> grid = {{1, 1}, {3, 4}};
  cout << sol.countPaths(grid) << "\n";
  return 0;
}