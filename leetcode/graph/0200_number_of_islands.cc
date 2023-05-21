#include <vector>
#include <utility>

using namespace std;

class Solution {
 public:
  int num;
  int numIslands(vector<vector<char>> &grid) {
    num = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] != '0' && grid[i][j] != '2') {
          Dfs(grid, {i, j});
          ++num;
        }
      }
    }
    return num;
  }

  void Dfs(vector<vector<char>> &grid, const pair<int, int> &pos) {
    if (min(pos.first, pos.second) < 0 || pos.first >= grid.size() || pos.second >= grid[0].size() ||
        grid[pos.first][pos.second] == '0' || grid[pos.first][pos.second] == '2') {
      return;
    }
    grid[pos.first][pos.second] = '2';
    Dfs(grid, {pos.first + 1, pos.second});
    Dfs(grid, {pos.first,     pos.second + 1});
    Dfs(grid, {pos.first - 1, pos.second});
    Dfs(grid, {pos.first,     pos.second - 1});
  }

};