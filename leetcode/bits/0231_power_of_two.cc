#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  static bool isPowerOfTwo(int n) {
    unsigned int nn = n;
    return n > 0 && (nn & (nn - 1)) == 0;
  }
};

int main() {
//  cout << Solution::isPowerOfTwo(16) << "\n";
//  cout << Solution::isPowerOfTwo(3) << "\n";
  cout << Solution::isPowerOfTwo(-2147483648) << "\n";
  return 0;
}