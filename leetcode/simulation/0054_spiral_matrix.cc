#include <vector>
#include <iostream>

using namespace std;

class Solution {
 public:
  // m == matrix.length
  // n == matrix[i].length
  // 1 <= m, n <= 10
  // -100 <= matrix[i][j] <= 100
  static vector<int> spiralOrder(vector<vector<int>> &matrix) {
    int x = 0, y = 0, dx = 1, dy = 0;
    int ch = (int)matrix[0].size(), rh = (int)matrix.size(), cl = 0, rl = 0;
    vector<int> result{matrix[y][x]};
    int size = static_cast<int>(ch * rh), index = 1;

    while (index < size) {
      x += dx;
      y -= dy;
      if (cl <= x && x < ch & rl <= y && y < rh) {
        result.push_back(matrix[y][x]);
        ++index;
      } else {
        x -= dx;
        y += dy;

        auto tmp = dx;
        dx = dy;
        dy = -tmp;

        if (!dx && dy < 0) {
          ++rl;
        } else if (!dx && dy > 0) {
          --rh;
        } else if (!dy && dx < 0) {
          --ch;
        } else {  // !dy && dx > 0
          ++cl;
        }
      }
    }
    return result;
  }
};

int main() {
  vector<vector<int>> input = {{1,2,3},{4,5,6},{7,8,9}};
//vector<vector<int>> input = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
  auto vec = Solution::spiralOrder(input);
  for (const auto &c : vec) {
    std::cout << c << "\n";
  }
  return 0;
}