#include <vector>
#include <algorithm>

using namespace std;
class Solution {
 public:
  int findMinArrowShots(vector<vector<int>> &points) {
    sort(points.begin(), points.end(),
         [](const vector<int> &lvec, const vector<int> &rvec) {
           return lvec[1] < rvec[1];
         });
    int ans = 1;
    int end = points[0][1];
    for(int i = 1; i < points.size(); ++i) {
      if (points[i][0] > end) {
        end = points[i][1];
        ++ans;
      }
    }
    return ans;
  }
};
