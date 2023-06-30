#include <vector>
#include <iostream>

using namespace std;

class Solution {
 public:
  enum Status{ Flood, Visited, Empty };

  int latestDayToCross(int row, int col, vector<vector<int>> &cells) {
    vector<vector<int>> visited(row + 1, vector<int>(col + 1, Empty));

    int hi = cells.size();
    int lo = 0;

    while (lo < hi) {
      int mid = (hi - lo) / 2 + lo;
      for (int i = 0; i < mid; ++i) {
        visited[cells[i][0]][cells[i][1]] = Flood;
      }
      if (Reachable(visited, row, col)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
      Restore(visited, row, col);
    }
    return --lo;
  }

  bool Reachable(vector<vector<int>> &visited, int Row, int Col) {
    bool reachable = false;
    for (int i = 1; i <= Col; ++i) {
      if (visited[1][i] == Empty) {
        reachable = Dfs(1, i, visited, Row, Col);
        if (reachable) {
          break;
        }
      }
    }
    return reachable;
  }

  void Restore(vector<vector<int>> &visited, int Row, int Col) {
    for (int r = 1; r <= Row; ++r) {
      for (int c = 1; c <= Col; ++c) {
        visited[r][c] = Empty;
      }
    }
  }


  bool Dfs(int row, int col, vector<vector<int>> &visited, int Row, int Col) {
    if (row == Row) return true;

    int dir[] = {0, -1, 0, 1, 0};
    visited[row][col] = Visited;

    for (int i = 1; i <= 4; ++i) {
      int r = row + dir[i - 1];
      int c = col + dir[i];
      if (r >= 1 && r <= Row && c >= 1 && c <= Col && visited[r][c] == Empty) {
        if (Dfs(r, c, visited, Row, Col)) {
          return true;
        }
      }
    }
    return false;
  }

};


int main() {

  Solution sol;

//  vector<vector<int>> cells{{1, 1}, {2, 1}, {1, 2}, {2, 2}};
//  cout << sol.latestDayToCross(2, 2, cells) << "\n";

//  vector<vector<int>> cells{{1, 1}, {1, 2}, {2, 1}, {2, 2}};
//  cout << sol.latestDayToCross(2, 2, cells) << "\n";

  vector<vector<int>> cells{{1, 2}, {2, 1}, {3, 3}, {2, 2}, {1, 1}, {1, 3}, {2, 3}, {3, 2}, {3, 1}};
  cout << sol.latestDayToCross(3, 3, cells) << "\n";


  return 0;
}