#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    vector<unordered_set<int>> mp(numCourses);
    vector<int> in(numCourses, 0);
    for (auto &item : prerequisites) {
      mp[item[1]].insert(item[0]);
      ++in[item[0]];
    }

    queue<int> queue;
    for (int i = 0; i < numCourses; ++i) {
      if (in[i] == 0) {
        queue.push(i);
      }
    }

    while (!queue.empty()) {
      auto p = queue.front(); queue.pop();
      --numCourses;

      for (auto &item : mp[p]) {
        if (--in[item] == 0) {
          queue.push(item);
        }
      }
    }
    return numCourses == 0;
  }
};

int main() {
  vector<vector<int>> pre{{1, 0}};
  Solution sol;
  cout << sol.canFinish(2, pre) << "\n";
  return 0;
}