#include <iostream>

using namespace std;

class Solution {
 public:
  static bool isPowerOfThree(int n) {
    return n > 0 && 1162261467 % n == 0;
  }
};