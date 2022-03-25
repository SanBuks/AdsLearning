#include <iostream>
#include <vector>

using namespace std;
class Solution {
 public:
  /**
   * m == obstacleGrid.length
   * n == obstacleGrid[i].length
   * 1 <= m, n <= 100
   * obstacleGrid[i][j] is 0 or 1.
   */
  static int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    vector<vector<int>> matrix(m, vector<int>(n));
    int i;
    for (i = 0; i < n && obstacleGrid[0][i] == 0; ++i) {
      matrix[0][i] = 1;
    }
    for (; i < n; ++i) {
      matrix[0][i] = 0;
    }

    for (i = 0; i < m && obstacleGrid[i][0] == 0; ++i) {
      matrix[i][0] = 1;
    }
    for (; i < m; ++i) {
      matrix[i][0] = 0;
    }

    for (int r = 1; r < m; ++r) {
      for (int c = 1; c < n; ++c) {
        if (obstacleGrid[r][c] == 0) {
          matrix[r][c] = matrix[r - 1][c] + matrix[r][c - 1];
        } else {
          matrix[r][c] = 0;
        }
      }
    }

    return matrix[m - 1][n - 1];
  }
};