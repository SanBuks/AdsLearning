#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
 public:
  static int M;

  int maximumRequests(int n, vector<vector<int>> &requests) {
    M = 0;
    for (int i = 0; i < requests.size(); ++i) {
      Dfs(i + 1, n, 0, requests);
      Dfs(i + 1, n, 1, requests);
    }
    return M;
  }

  void Dfs(int i, int n, unsigned int status, vector<vector<int>> &requests) {
    if (i == requests.size()) {
      vector<int> record(n, 0);

      // 遍历每一个 requests
      for (int k = 0; k < requests.size(); ++k) {
        // 如果包含
        if (1 << k & status) {
          --record[requests[k][0]];
          ++record[requests[k][1]];
        }
      }

      bool success = true;
      for (auto &item : record) {
        if (item != 0) {
          success = false;
          break;
        }
      }
      if (success) {
        int bit_count = 0;
        for (int k = 0; k < 16; ++k) {
          if (1 << k & status) {
            ++bit_count;
          }
        }
        M = max(M, bit_count);
      }
      return;
    }

    Dfs(i + 1, n, status, requests);
    status |= 1 << i;
    Dfs(i + 1, n, status, requests);
  }
};
int Solution::M;

int main() {
  Solution sol;

//  vector<vector<int>> re{{0, 1}, {1, 0}, {0, 1}, {1, 2}, {2, 0}, {3, 4}};
//  cout << sol.maximumRequests(5, re) << "\n";

//  vector<vector<int>> re{{0, 0}, {1, 2}, {2, 1}};
//  cout << sol.maximumRequests(3, re) << "\n";


//  {{1,2},{1,2},{2,2},{0,2},{2,1},{1,1},{1,2}}

  return 0;
}