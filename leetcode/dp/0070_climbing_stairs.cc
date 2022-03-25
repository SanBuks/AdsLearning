#include <iostream>

class Solution {
 public:
  static int climbStairs(int n) {
    int pre = 1;
    int now = 2;

    if (n == 1) {
      return pre;
    }
    if (n == 2) {
      return now;
    }

    int sum = 0;

    for (int i = 3; i <= n; ++i) {
      sum = pre + now;
      pre = now;
      now = sum;
    }
    return sum;
  }
};

int main () {
  std::cout << Solution::climbStairs(4) << "\n";
  return 0;
}