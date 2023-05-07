#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
 public:
  static vector<int>
  longestObstacleCourseAtEachPosition(vector<int> &ob) {
    auto size = static_cast<int>(ob.size());
    vector<int> result(size, 1), sub{ob[0]};
    for (int i = 1; i < size; ++i) {
      if (ob[i] >= sub[sub.size() - 1]) {
        sub.push_back(ob[i]);
        result[i] = static_cast<int>(sub.size());
      } else {
        auto it = upper_bound(sub.begin(), sub.end(), ob[i]);  // upper_bound 2 2 3 <- 2 = 2 2 2
        *it = ob[i];
        result[i] = static_cast<int>(it - sub.begin() + 1);
      }
    }
    return result;
  }
};

int main() {
//  vector<int> vec{3, 1, 5, 6, 4, 2};
  vector<int> vec{1, 2, 3, 2};

  auto vec_= Solution::longestObstacleCourseAtEachPosition(vec);
  return 0;
}
