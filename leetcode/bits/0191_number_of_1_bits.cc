#include <iostream>

using namespace std;

using ull = unsigned long long;

inline ull Pow(ull n) {
  return 1ULL << n;
}

/**
 * 0 <= n <= 5
 * -1 / 2^0 + 1 = error
 * -1 / 2^1 + 1 = 0101 0101
 * -1 / 2^2 + 1 = 0011 0011
 * -1 / 2^4 + 1 = 0000 1111
 * -1 / 2^8 + 1 = 0000 1111
 */
ull Mask(ull n) {
  n %= 6;
  return -1ULL / (Pow(Pow(n)) + 1);
}

ull Process(ull num, ull n) {
  auto mask = Mask(n);
  return (num & mask) + (num >> Pow(n) & mask);
}

class Solution {
 public:
  static int hammingWeight(uint32_t n) {
    for (int i = 0; i < 5/* log2(sizeof(unint32_t)*8) */; ++i) {
      n = Process(n, i);
    }
    return static_cast<int>(n);
  }
};

int main() {
  cout <<  Solution::hammingWeight(11);
  return 0;
}