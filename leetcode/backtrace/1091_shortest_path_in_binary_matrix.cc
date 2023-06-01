#include <vector>
#include <queue>
#include <iostream>
using namespace std;
class Solution {
 public:
  queue<pair<int, int>> queue_;
  int xh, yh;
  int path;

  int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
    while (!queue_.empty()) queue_.pop();
    xh = static_cast<int>(grid.size());
    yh = static_cast<int>(grid[0].size());
    path = 0;

    if (grid[0][0] == 1 || grid.back().back()) {
      return -1;
    }
    int dxy[] = {-1, -1, 1, 1, -1, 0, 1, 0, -1};

    size_t round_num;
    queue_.emplace(0, 0);
    while (!queue_.empty()) {
      ++path;
      round_num = queue_.size();
      while (round_num) {
        auto pos = queue_.front(); queue_.pop();
        if (pos.first == xh - 1 && pos.second == yh - 1) {
          return path;
        }
        for (int i = 0; i < 8; ++i) {
          auto next_pos = make_pair(pos.first + dxy[i], pos.second + dxy[i + 1]);
          if (next_pos.first < 0 || next_pos.first >= xh ||
              next_pos.second < 0 || next_pos.second >= yh ||
              grid[next_pos.first][next_pos.second] == 2 ||
              grid[next_pos.first][next_pos.second] == 1) {
            continue;
          } else {
            grid[next_pos.first][next_pos.second] = 2;
            queue_.push(next_pos);
          }
        }
        --round_num;
      }
    }
    return -1;
  }
};

int main() {
//  vector<vector<int>> grid = {{0, 0, 0}, {1, 1, 0}, {1, 1, 0}};
//  vector<vector<int>> grid = {{1, 0, 0}, {1, 1, 0}, {1, 1, 0}};

//  vector<vector<int>> grid = {{1, 0, 0}, {1, 1, 0}, {1, 1, 0}};

  vector<vector<int>> grid =
      {{0, 0, 1, 1, 0, 0},
       {0, 0, 0, 0, 1, 1},
       {1, 0, 1, 1, 0, 0},
       {0, 0, 1, 1, 0, 0},
       {0, 0, 0, 0, 0, 0},
       {0, 0, 1, 0, 0, 0}};

  Solution sol;
  cout << sol.shortestPathBinaryMatrix(grid) << "\n";
  return 0;
}