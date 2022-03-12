#include <vector>
#include <iostream>

using namespace std;

class Solution {
 public:
  static vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> result(n, vector<int>(n));
    result[0][0] = 1;
    int index = 1, size = n * n, num = 2;
    int x = 0, y = 0, dx = 1, dy = 0, ch = n, rh = n, cl = 0, rl = 0;
    while (index < size) {
      x += dx;
      y -= dy;
      if (cl <= x && x < ch && rl <= y && y < rh) {
        result[y][x] = num++;
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
  auto vec = Solution::generateMatrix(3);
  for (const auto &c : vec) {
    for (const auto &b : c) {
      std::cout << b << "\n";
    }
  }
  return 0;
}