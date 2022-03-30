#include <iostream>

using namespace std;

int mask = 0x55555555;
class Solution {
 public:
  static bool isPowerOfFour(int n) {
    return n > 0 && (n & (n - 1)) == 0 && (n | mask) == mask;
//    return n > 0 && (n & (n - 1)) == 0 && (n - 1) % 3 == 0;
//    (4^n-1) = (4-1) (4^(n-1) + 4^(n-2) + 4^(n-3) + ..... + 4 + 1)
  }
};