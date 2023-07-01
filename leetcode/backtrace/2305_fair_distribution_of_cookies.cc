#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
 public:
  static int CookiesNum;

  int distributeCookies(vector<int> &cookies, int k) {
    CookiesNum = numeric_limits<int>::max();
    vector<int> dist(k, 0);
    for (int i = 0; i < k; ++i) {
      dist[i] += cookies[0];
      Dfs(0, cookies, dist);
      dist[i] -= cookies[0];
    }
    return CookiesNum;
  }

  void Dfs(int index, vector<int> &cookies, vector<int> &dist) {
    if (index == cookies.size() - 1) {
      int m = -1;
      for (int item : dist) {
        m = max(m, item);
      }
      CookiesNum = min(CookiesNum, m);
      return ;
    }

    for (int i = 0; i < dist.size(); ++i) {
      dist[i] += cookies[index + 1];
      Dfs(index + 1, cookies, dist);
      dist[i] -= cookies[index + 1];
    }
  }
};

int Solution::CookiesNum;

int main() {
  Solution sol;

//  vector<int> vec{8, 15, 10, 20, 8};
//  cout << sol.distributeCookies(vec, 2) << "\n";

  vector<int> vec{6, 1, 3, 2, 2, 4, 1, 2};
  cout << sol.distributeCookies(vec, 3) << "\n";

  return 0;
}