#include <iostream>

using namespace std;

/**
 *  easy 二分查找
 */
class Solution {
 public:
  bool static isPerfectSquare(int num) {
    // 1 <= num <= 2^31 - 1
    if (num == 1) {
      return true;
    }
    int lo = 1;
    int hi = num;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      unsigned long long temp = mid;
      temp *= temp;
      if (temp > num) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    --lo;
    unsigned long long temp = lo;
    temp *= temp;
    if (temp == num) {
      return true;
    } else {
      return false;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  std::cout << Solution::isPerfectSquare(16);
  return 0;
}
