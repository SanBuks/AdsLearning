#include <unordered_map>
#include <vector>
using std::vector;
using std::unordered_map;

/*
 * easy 哈希
 * 如果用 int 数组 需要 8GB 内存空间
 */
class Solution {
 public:
  vector<int> twoSum(vector<int> &nums, int target) {
    std::unordered_map<int, size_t> hash;
    for (size_t i = 0; i != nums.size(); ++i) {
      int target_num = target - nums[i];
      if (hash.find(target_num) != hash.end()) {
        return {static_cast<int>(hash[target_num]), static_cast<int>(i)};
      }
      hash.emplace(nums[i], i);
    }
    return {};
  }
};
































