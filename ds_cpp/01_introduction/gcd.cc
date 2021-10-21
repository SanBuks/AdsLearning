#include <iostream>

unsigned long Gcd(unsigned long a, unsigned long b) {
  unsigned long p = 0;
  while (!((a & 1) || (b & 1))) {
    a >>= 1;
    b >>= 1;
    ++p;
  }

  while (true) {
    while (!(a & 1)) {
      a >>= 1;
    }
    while (!(b & 1)) {
      b >>= 1;
    }

    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }

    if (a == 0) {
      return b << p; 
    } 
    if (b == 0) {
      return a << p;
    }
  }
}


int main() {
  std::cout << Gcd(18, 2);
  return 0;
}