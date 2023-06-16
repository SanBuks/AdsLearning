#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;
class Solution {
 public:
  unordered_map<int, vector<int>> mp;
  //100010
  int numOfMinutes(int n, int headID, vector<int> &manager, vector<int> &informTime) {
    if (n == 1) return 0;

    for (int i = 0; i < manager.size(); ++i) {
      mp[manager[i]].emplace_back(i);
    }
    return Dfs(headID, 0, informTime);
  }

  int Dfs(int index, int path_size, const vector<int> &informTime) {
    path_size += informTime[index];
    int max_path_size = path_size;
    for (int i : mp[index]) {
      max_path_size = max(max_path_size, Dfs(i, path_size, informTime));
    }
    return max_path_size;
  }

};

struct Example {
  int n = 22;
  int headId = 7;
  vector<int> manager{12, 7, 18, 11, 13, 21, 12, -1, 6, 5, 14, 13, 14, 9, 20, 13, 11, 1, 1, 2, 3, 19};
  vector<int> informTime{0, 540, 347, 586, 0, 748, 824, 486, 0, 777, 0, 202, 653, 713, 454, 0, 0, 0, 574, 735, 721, 772};
};

//struct Example {
//  int n = 6;
//  int headId = 2;
//  vector<int> manager {2,2,-1,2,2,2};
//  vector<int> informTime {0,0,1,0,0,0};
//};

int main() {
  Solution sol;
  Example e;
  cout << sol.numOfMinutes(e.n, e.headId, e.manager, e.informTime) << "\n";
  return 0;
}