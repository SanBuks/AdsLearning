#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class Solution {
 public:
  int shortestPathAllKeys(vector<string> &grid) {
    int path = 0;
    int K = 0;
    int m = grid.size();
    int n = grid[0].size();
    int dir[5] = {0, 1, 0, -1, 0};

    queue<pair<int, int>> queue;
    vector<vector<vector<bool>>> visit(m, vector<vector<bool>>(n, vector<bool>(1 << K, false)));

    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        if (grid[r][c] == '@') {
          queue.emplace(r * m + c, 0);
          visit[r][c][0] = true;
        }
        if (grid[r][c] >= 'A' && grid[r][c] <= 'Z') {
          ++K;
        }
      }
    }


    while(!queue.empty()) {
      int size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto pair = queue.front(); queue.pop();
        if (pair.second == K - 1) { return path; }
        int r = pair.first / n;
        int c = pair.first % n;
        int k = pair.second;
        for (int j = 1; j <= 4; ++j) {
          int rr = r + dir[j - 1];
          int cc = c + dir[j];
          if (rr < 0 || rr >= m || cc < 0 || cc >= n || grid[rr][cc] == '#' || visit[rr][cc][k]) {
            continue;
          }
          if (grid[rr][cc] <= 'z' && grid[rr][cc] >= 'a') {
            k = grid[rr][cc] - 'z' | k;
          }
        }

      }
    }
    return -1;
  }
};



int main() {


  return 0;
}