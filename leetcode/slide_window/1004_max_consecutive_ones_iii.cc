#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Solution {
 public:
  int longestOnes(vector<int> &nums, int k) {
    int ans = 0;
    int zero = 0;
    int low = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 0) {
        ++zero;
      }
      while (zero > k) {
        if (nums[low] == 0) {
          --zero;
        }
        ++low;
      }
      ans = max(ans, i - low + 1);
    }
    return ans;
  }
};

int main() {
  Solution sol;

//  vector<int> nums{1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
//  cout << sol.longestOnes(nums, 2) << "\n";

  vector<int> nums{0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
  cout << sol.longestOnes(nums, 3) << "\n";
  return 0;
}