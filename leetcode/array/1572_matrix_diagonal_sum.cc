#include <vector>

using namespace std;

class Solution {
 public:
  static int diagonalSum(vector<vector<int>> &mat) {
    int sum = 0;
    int size = static_cast<int>(mat.size());
    int i = 0, j = 0;
    while (i < size) {
      sum += mat[i][j];
      ++i;
      ++j;
    }
    i = 0, j = size - 1;
    while (i < size) {
      sum += mat[i][j];
      ++i;
      --j;
    }
    sum -= size % 2 ? mat[size/ 2][size / 2]: 0;
    return sum;
  }
};