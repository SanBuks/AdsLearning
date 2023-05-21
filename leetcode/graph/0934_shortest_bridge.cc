#include <vector>
#include <utility>
#include <queue>
#include <iostream>
using namespace std;
class Solution {
 public:
  int result;
  int size;
  queue<pair<int, int>> queue;
  int var[5] = {0, -1, 0, 1, 0};
  int shortestBridge(vector<vector<int>> &grid) {
    result = 0;
    size = static_cast<int>(grid.size());
    while(!queue.empty()) queue.pop();
    MarkFirstLand(grid);
    ExpandByRound(grid);
    return result;
  }

  void ExpandByRound(vector<vector<int>> &grid) {
    bool find = false;
    while (!find) {
      auto num = queue.size();
      for (int i = 0; i < num && !find; ++i) {
        pair<int, int> pos = queue.front();
        queue.pop();
        for (int j = 0; j < 4; ++j) {
          int ii = pos.first + var[j];
          int jj = pos.second + var[j + 1];
          if (min(ii, jj) < 0 || max(ii, jj) >= size) continue;
          if (grid[ii][jj] == 0) {
            grid[ii][jj] = 2;
            queue.emplace(ii, jj);
          } else if (grid[ii][jj] == 1) {
            find = true;
            break;
          }
        }
        queue.push(pos);
      }
      if (!find) ++result;
    }
  }

  void MarkFirstLand(vector<vector<int>> &grid) {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (grid[i][j] == 1) {
          Dfs(grid, {i, j});
          goto b;
        }
      }
    }
    b: return;
  }

  void Dfs(vector<vector<int>> &grid, const pair<int, int> &pos) {
    if (min(pos.first, pos.second) < 0 || max(pos.first, pos.second) >= size ||
        grid[pos.first][pos.second] == 0 || grid[pos.first][pos.second] == 2) {
      return;
    }
    queue.push(pos);
    grid[pos.first][pos.second] = 2;
    Dfs(grid, {pos.first, pos.second + 1});
    Dfs(grid, {pos.first + 1, pos.second});
    Dfs(grid, {pos.first, pos.second - 1});
    Dfs(grid, {pos.first - 1, pos.second});
  }
};


int main() {
  Solution sol;
  vector<vector<int>> grid{{0, 1}, {1, 0}};
  sol.shortestBridge(grid);
  return 0;
}