#include <iostream>

using namespace std;

/**
 *  easy 二分查找
 */
class Solution {
 public:
  static int mySqrt(int x) {
    if (x == 1) {
      return 1;
    }
    if (!x) {
      return 0;
    }
    int lo = 1;
    int hi = x;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      // 0 <= x   <= 2^31 - 1
      // 0 <= x^2 <= 2^62 - 2^32 + 1
      unsigned long long temp = mid;
      temp *= temp;
      if (temp > x) {  // [hi, size) > sqrt(x)
        hi = mid;
      } else {         // [0, lo) <= sqrt(x)
        lo = mid + 1;
      }
    }
    return --lo;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  std::cout << Solution::mySqrt(8);
  return 0;
}