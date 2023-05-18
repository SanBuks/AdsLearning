#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
class Solution {
 public:
  static constexpr const int kModSize = 1e9 + 7;
  static int numSubseq(vector<int> &nums, int target) {
    int result = 0;
    int size = static_cast<int>(nums.size());
    sort(nums.begin(), nums.end());
    int left = 0, right = size -1;
    while (left <= right) {
      if (nums[right] + nums[left] <= target) {
        auto pow_result = static_cast<int>(power(2, right - left));
        result = (result + pow_result) % kModSize;
        ++left;
      } else {
        --right;
      }
    }
    return result;
  }
  long long static power(long long x, long long y) {
    if (y == 1) return x;
    if (y == 0) return 1;
    long long ans = 1;
    if (y % 2 == 0) {
      ans = power(x, y / 2);
      ans *= ans;
    } else {
      ans = power(x, y - 1);
      ans *= x;
    }
    return ans % kModSize;
  }
  static long long pow2(long long num) {
    if (num == 0) return 1;
    long long result = 1;
    for (int i = 0; i < num; ++i) {
      result = (result << 1) % kModSize;
    }
    return result;
  }

  static int numSubseq_brute(vector<int> &nums, int target) {
    int size = static_cast<int>(nums.size());
    int result = 0;
    int pow_size = 1 << size;
    int max, min;

    for (int i = 1; i < pow_size; ++i) {
      max = numeric_limits<int>::min();
      min = numeric_limits<int>::max();
      for (int j = 0; j < size; ++j) {
        if ((1 << j) & i) {
          max = nums[j] > max ? nums[j] : max;
          min = nums[j] < min ? nums[j] : min;
        }
      }
      if (max + min <= target) {
        result = (result + 1) % kModSize;
      }
    }

    return result;
  }
};

int main() {
  vector<int> vec{2,3,3,4,6,7};
  std::cout << Solution::numSubseq(vec, 12) << "\n";
  return 0;
}