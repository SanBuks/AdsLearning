#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
 public:
  int longestSubarray(vector<int> &nums) {
    int ans = 0;
    int low = 0;  // 1 / 0
    int mid = -1; //     0
    int high = 0; //     0 / end
    for (int i = low; i < nums.size(); ++i) {
      if (nums[i] == 0) {
        mid = i;
        break;
      }
    }
    if (mid == -1) {
      return nums.size() - 1;
    }
    for (high = mid + 1; high < nums.size(); ++high) {
      if (nums[high] == 0) {
        ans = max(ans, high - low - 1);
        low = mid + 1;
        mid = high;
      }
    }
    ans = max(ans, static_cast<int>(nums.size()) - low - 1);

    return ans;
  }
};


int main() {
  Solution sol;

//  vector<int> nums{1, 1, 1};
//  vector<int> nums{1, 1, 0, 1};
//  vector<int> nums{0, 1, 1, 1, 0, 1, 1, 0, 1};
  vector<int> nums{0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0};
  cout << sol.longestSubarray(nums) << "\n";
  return 0;
}
