#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
/*
 * easy 哈希
 * 如果用 int 数组 需要 8GB 内存空间
 *
 *
 */
class Solution {
 public:
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, size_t> hash;
    for (size_t i = 0; i != nums.size(); ++i) {
      int target_num = target - nums[i];
      if (hash.find(target_num) != hash.end()) {
        return {static_cast<int>(hash[target_num]), static_cast<int>(i)};
      }
      hash.emplace(nums[i], i);
    }
    return {};
  }

  vector<vector<int>> twoSumAllPair(vector<int> &nums, int target) {
    nums.

  }
};
