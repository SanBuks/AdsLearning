#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  /**
   * 迭代
   */
  static vector<vector<int>> subsetsWithDup1(vector<int> &nums) {
    std::vector<std::vector<int>> result{{}};
    sort(nums.begin(), nums.end());

    size_t i = 0;
    while (i != nums.size()) {
      size_t times = 1;  // 元素是否出现重复
      size_t j = i + 1;  // 指向下一个不重复的数
      while (j != nums.size() && nums[j] == nums[i]) {
        ++times;
        ++j;
      }

      size_t old_size = result.size();
      for (size_t t = 0; t != times; ++t) {
        // 增加元素
        result.resize(result.size() + old_size);
        auto last_it = result.begin() + (t + 1) * old_size;
        copy(result.begin(), result.begin() + old_size, last_it);
        // 修改元素
        for (auto it = last_it; it != result.end(); ++it) {
          for (int cc = 0; cc < t + 1; ++cc) {
            it->push_back(nums[i]);
          }
        }
      }
      i = j;  // 更新
    }
    return result;
  }

  /**
   *  回溯
   */
  static vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    std::vector<std::vector<int>> result{};
    std::vector<int> vec;
    subsetsWithDupI(nums, result, vec, 0);
    return result;
  }

  static void subsetsWithDupI(vector<int> &nums, vector<vector<int>> &result,
                              vector<int> &vec, size_t cur) {
    result.push_back(vec);
    for (size_t j = cur; j < nums.size(); ++j) {
      if (j == cur || nums[j] != nums[j - 1]) {
        vec.push_back(nums[j]);
        subsetsWithDupI(nums, result, vec, j + 1);
        vec.pop_back();
      }
    }
  }
};

int main() {
//  vector<int> a {5, 5, 5, 5, 5};
//  vector<int> a {1, 2, 2, 3};
  vector<int> a {1, 2, 2};
  auto it = Solution::subsetsWithDup(a);
  for (const auto &first : it) {
    for (const auto &second : first) {
      std::cout << second << " ";
    }
    std::cout << "\n";
  }
  return 0;
}