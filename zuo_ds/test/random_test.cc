#include <iostream>
#include "randomor.h"

void RandomTest() {
  std::cout << zuo::RandomGenerator<int>::RandomScalaElem({3, 4}) << "\n";
  std::cout << zuo::RandomGenerator<double>::RandomScalaElem({3.33, 4.44}) << "\n";

  auto array1 = zuo::RandomGenerator<int>::RandomScalaArray(10, {3, 4});
  for (int i = 0; i < 10; ++i) { std::cout << array1[i] << " "; }
  std::cout << "\n";
  auto array2 = zuo::RandomGenerator<double>::RandomScalaArray(10, {3.33, 4.44});
  for (int i = 0; i < 10; ++i) { std::cout << array2[i] << " "; }
  std::cout << "\n";
}

int main() {
  RandomTest();
  return 0;
}