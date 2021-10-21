#include <iostream>

static int times = 0;
int ackermann(int m, int n) {
  ++times;
  if (m == 0) {
    return n + 1;
  }
  else if (m > 0 && n==0 ) {
    return ackermann(m-1, 1);
  }
  else {
    int temp = ackermann(m, n-1);
    return ackermann(m-1, temp);
  }
}

int main() {
  std::cout << ackermann(3, 3) << "\n";
  std::cout << times;
  return 0;
}