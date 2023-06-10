#include <algorithm>
#include <vector>

using namespace std;

class Solution {
 public:
  static int countNegatives(vector<vector<int>> &grid) {
    int ans = 0;

    const int row = static_cast<int>(grid.size());
    const int col = static_cast<int>(grid[0].size());

    int i = row - 1;
    int j = 0;

    while (j < grid[0].size()) {
      while(i >= 0 && grid[i][j] < 0) {
        --i;
      }
      ans += row - i - 1;
      ++j;
    }

    return ans;
  }
};
