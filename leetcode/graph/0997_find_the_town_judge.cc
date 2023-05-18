#include <vector>
#include <cstring>
using namespace std;
class Solution {
 public:
  static int degree[1010][2]; // [0]:out [1]:in
  int findJudge(int n, vector<vector<int>> &trust) {
    memset(degree, 0, sizeof(degree));
    for (auto &item : trust) {
      ++degree[item[0]][0];
      ++degree[item[1]][1];
    }
    for (int i = 1; i <= n; ++i) {
      if (degree[i][0] == 0 && degree[i][1] == n-1) {
        return i;
      }
    }
    return -1;
  }
};

int Solution::degree[1010][2];
