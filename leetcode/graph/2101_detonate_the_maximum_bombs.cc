#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;
class Solution {
 public:
  enum Status { Unused = 0, Used };
  unordered_map<int, vector<int>> mp;
  int maximumDetonation(const vector<vector<int>> &bombs) {
    mp.clear();
    CreateMap(bombs);
    if (mp.empty()) return 1;
    vector<int> flag(bombs.size(), Status::Unused);

    int ans = numeric_limits<int>::min();
    for (int i = 0; i < bombs.size(); ++i) {
      for (auto &item : flag) { item = Status::Unused; }
      ans = max(ans, Dfs(i, bombs, flag));
    }
    return ans;
  }

  void CreateMap(const vector<vector<int>> &bombs) {
    for (int i = 0; i < bombs.size(); ++i) {
      mp.emplace(i, vector<int>{});
    }
    for (int i = 0; i < bombs.size(); ++i) {
      for (int j = 0; j < bombs.size(); ++j) {
        if (i == j) continue;
        pair<int, int> bombs_pos{bombs[j][0], bombs[j][1]};
        pair<int, int> denote_pos{bombs[i][0], bombs[i][1]};
        int radian = bombs[i][2];
        if (JudgeRange(bombs_pos, denote_pos, radian)) {
          mp[i].push_back(j);
        }
      }
    }
  }

  static bool JudgeRange(pair<int, int> bombs_pos, pair<int, int> denote_pos, int radian) {
    double dx = bombs_pos.first - denote_pos.first;
    double dy = bombs_pos.second - denote_pos.second;
    return sqrt(dx * dx + dy * dy) <= radian * 1.0;
  }

  int Dfs(int index, const vector<vector<int>> &bombs, vector<int> &flag) {
    int path_size = 1;
    flag[index] = Status::Used;
    for (int i = 0; i < mp[index].size(); ++i) {
      int next_index = mp[index][i];
      if (flag[next_index] == Status::Used) continue;
      path_size += Dfs(next_index, bombs, flag);
    }
    return path_size;
  }
};


int main() {
  Solution sol;
  vector<vector<int>> bombs = {{1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}};
//  vector<vector<int>> bombs = {{2,1,3},{6,1,4}};  // 2
//  vector<vector<int>> bombs = {{1,1,5},{10,10,5}}; // 1

  cout << sol.maximumDetonation(bombs) << "\n";
}