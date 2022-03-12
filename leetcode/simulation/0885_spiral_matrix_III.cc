#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  static vector<vector<int>> spiralMatrixIII(int r, int c, int y, int x) {
    vector<vector<int>> result{{y, x}};
    int index = 1;
    int n = 0;
    int dx = 1, dy = 0;
    // 右手法则
    // (dx, dy, 0) x (0, 0, 1) = (y1z2 - z1y2, z1x2 - x1z2, x1y2 - y1x2)
    //                         = (dy * 1, -dx * 1, 0)
    while (index < r * c) {
      for (int _i = 0; _i < n / 2 + 1; ++_i) {
        x = x + dx;
        y = y - dy;
        if (0 <= x && x < c && 0 <= y && y < r) {
          ++index;
          result.push_back({y, x});
        }
      }
      auto temp = dx;
      dx = dy;
      dy = -temp;
      ++n;
    }
    return result;
  }
};

int main() {
  auto r = Solution::spiralMatrixIII(5, 6, 1, 4);
  for (auto const &i : r) {
    std::cout << "[";
    for (auto const &j : i) {
       std::cout << j << " ";
    }
    std::cout << "]\n";
  }
  return 0;
}
