#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 区间问题

// Greedy:
// sweeping line  -> calc

// DP
// starting point -> minimum to cover
// ending point   -> maximum to no overlapping

class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end(),
         [](vector<int> &lvec, vector<int> &rvec) {
           return lvec[1] < rvec[1];
         });

    int ans = 1;
    int end = intervals[0][1];

    for (int i = 1; i < intervals.size(); ++i) {
      if (intervals[i][0] >= end) {
        end = intervals[i][1];
        ++ans;
      }
    }
    return static_cast<int>(intervals.size()) - ans;
  }
};

int main() {
//  vector<vector<int>> intervals {{1,100},{11,22},{1,11},{2,12}};
  vector<vector<int>> intervals {{-52, 31}, {-73, -26}, {82, 97}, {-65, -11}, {-62, -49}, {95, 99}, {58, 95}, {-31, 49}, {66, 98}, {-63, 2}, {30, 47}, {-40, -26}};
  Solution sol;
  cout << sol.eraseOverlapIntervals(intervals) << "\n";

  return 0;
}