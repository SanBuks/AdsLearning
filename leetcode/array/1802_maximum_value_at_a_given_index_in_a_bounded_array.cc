#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
 public:
  static int maxValue(int n, int index, int maxSum) {
    int lo = 1, hi = (maxSum - n + 1) + 1;

    while (lo < hi) {
      int mid = (hi - lo) / 2 + lo;
      if (calc(n, index , mid, maxSum) < 0) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    return --lo;
  }

  static int calc(int n, int index, int target, int maxSum) {
    // 计算 [0 ~ index - 1] 数值
    long long lo_sum = 0;
    // 0 1, 2, 3, [4]=5
    // 0 1, 2, 3, [4]=6
    // 0 1, 2, 3, [4]=4
    int num = min(index - 0, target - 1);
    long long start = target - num;
    long long end = target - 1;
    lo_sum = (start + end) * num / 2;  // 存在 int 型不够用情况
    if (index - 0 > num) {
      lo_sum += index - 0 - num;
    }

    // 计算 [index + 1 ~ n - 1] 数值
    long long hi_sum = 0;
    // [4]=5, 5, 6, 7, 8 (9)
    num = min(n - 1 - index, target - 1);
    start = target - num;
    end = target -1;
    hi_sum = (start + end) * num / 2;
    if (n - 1 - index > num) {
      hi_sum += n - 1 - index - num;
    }

    // 判断容量是否超过
    if (maxSum - lo_sum - hi_sum - target < 0) {
      return -1;
    } else {
      return 1;
    }
  }
};


int main() {
  Solution sol;
//  cout << sol.maxValue(4, 2, 6) << "\n";
//  cout << sol.maxValue(6, 1, 10) << "\n";
  cout << sol.maxValue(7, 0, 930041194) << "\n";
  // (7, 0, 930041194)
  return 0;
}