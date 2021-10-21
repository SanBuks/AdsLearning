#include "fib.h"

#include <iostream>

int main() {
  Fib fib(100);
  std::cout << fib.get() << "\n";
  std::cout << fib.prev() << "\n";
  std::cout << fib.prev() << "\n";
  std::cout << fib.prev() << "\n";
  std::cout << fib.prev() << "\n";
  std::cout << fib.prev() << "\n";
  std::cout << fib.prev() << "\n";
  std::cout << fib.prev() << "\n";

  return 0;
}