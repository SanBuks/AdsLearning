#include <iostream>
#include <vector>

using namespace std;

/**
 * DP
 * 深搜
 * 组合计算
 */
class Solution {
 public:
  static int uniquePaths(int m, int n) {
    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < n; ++i) {
      matrix[0][i] = 1;
    }
    for (int i = 0; i < m; ++i) {
      matrix[i][0] = 1;
    }

    for (int r = 1; r < m; ++r) {
      for (int c = 1; c < n; ++c) {
        matrix[r][c] = matrix[r - 1][c] + matrix[r][c - 1];
      }
    }
    return matrix[m - 1][n -1];

  }
};

int main () {
  std::cout << Solution::uniquePaths(3, 2) << "\n";
  return 0;
}