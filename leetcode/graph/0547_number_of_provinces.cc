#include <vector>
#include <iostream>

using namespace std;

class Solution {
 public:
  int findCircleNum(vector<vector<int>> &isConnected) {
    int size = static_cast<int>(isConnected.size());
    int ans = 0;
    vector<bool> flag(size, false);
    for (int i = 0; i < size; ++i) {
      if (!flag[i]) {
        ++ans;
        Dfs(i, isConnected, flag);
      }
    }
    return ans;
  }

  void Dfs(int index, const vector<vector<int>> &isConnected, vector<bool> &flag) {
    flag[index] = true;
    for (int i = 0; i < isConnected.size(); ++i) {
      if (i == index) continue;
      if (isConnected[index][i] && !flag[i]) {
        Dfs(i, isConnected, flag);
      }
    }
  }
};

int main() {
  Solution sol;
  vector<vector<int>> isConnected{{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
  cout << sol.findCircleNum(isConnected) << "\n";
  return 0;
}