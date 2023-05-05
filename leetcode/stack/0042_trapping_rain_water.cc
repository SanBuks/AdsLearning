#include <vector>
#include <iostream>
using namespace std;
class Solution {
 public:
  static int trap(vector<int> &height) {
    int size = static_cast<int>(height.size());
    int result = 0;
    if (size < 3) { return result; }
    return result;
  }

  static int trap_two_pointer(vector<int> &height) {
    int size = static_cast<int>(height.size());
    int result = 0;
    if (size < 3) { return result; }

    // left_max[i]: 0, 1, 2, 3, i - 1, i 内最大值
    vector<int> left_max(size, 0); left_max[0] = height[0];
    vector<int> right_max(size, 0); right_max[size - 1] = height[size - 1];
    for (int i = 1; i < size; ++i) {
      left_max[i] = max(height[i], left_max[i - 1]);
    }
    for (int i = size - 2; i >= 0; --i) {
      right_max[i] = max(height[i], right_max[i + 1]);
    }

    int temp_result = 0;
    for (int i = 1; i < size - 1; ++i) {
      temp_result = min(left_max[i - 1], right_max[i + 1]) - height[i];
      result += temp_result > 0 ? temp_result : 0;
    }
    return result;
  }

  static int trap_brutal(vector<int> &height) {
    int size = static_cast<int>(height.size());
    int result = 0;
    if (size < 3) { return result; }

    for (int i = 1; i < size - 1; ++i) {
      int left = 0;
      for (int j = i - 1; j >= 0; --j) {
        left = height[j] > left ? height[j] : left;
      }
      int right = 0;
      for (int j = i + 1; j < size; ++j) {
        right = height[j] > right ? height[j] : right;
      }
      auto temp_result = min(left, right) - height[i];
      result += temp_result > 0 ? temp_result : 0;
    }

    return result;
  }
};

int main() {
  vector<int> vec{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  std::cout << Solution::trap(vec);
  return 0;
}