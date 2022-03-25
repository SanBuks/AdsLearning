#include <vector>
#include <algorithm>

using namespace std;

/**
 * 三种解法
 */
class Solution {
 public:
  // 1 <= nums.length <= 10
  static vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> vec{{}};
    std::sort(nums.begin(), nums.end());
    for (const auto &item : nums) {

    }
    return vec;
  }
};

int main() {

}