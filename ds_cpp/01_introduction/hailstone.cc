#include <iostream>

unsigned long HailStone(unsigned long n) {
  unsigned long times = 0;
  while ( 1 < n) {
    if (n % 2) {
      n = 3 * n + 1;
    } else {
      n >>= 1;
    }
    ++times;
  }
  ++times;
  return times;
}

int main() {
  std::cout << HailStone(11);
  return 0;
}