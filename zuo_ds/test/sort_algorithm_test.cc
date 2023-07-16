#include <iostream>
#include <utility>

#include "comparator.h"

template<typename T>
void static SelectSort(T array[], size_t n) {
  if (!array || n < 2) return;

  size_t min_index;
  for (size_t i = 0; i < n - 1; ++i) {
    min_index = i;
    for (size_t j = i + 1; j < n; ++j) {
      min_index = array[j] < array[min_index] ? j : min_index;
    }
    std::swap(array[i], array[min_index]);
  }
}

int main() {
  std:: cout << zuo::RandomGenerator<int>::RandomScalaElem({3, 4}) << "\n";
  std:: cout << zuo::RandomGenerator<double>::RandomScalaElem({3.33, 4.44}) << "\n";

  auto array1 = zuo::RandomGenerator<int>::RandomScalaArray(10, {3, 4});
  for (int i = 0; i < 10; ++i) { std::cout << array1[i] << " "; }
  std::cout << "\n";
  auto array2 = zuo::RandomGenerator<double>::RandomScalaArray(10, {3.33, 4.44});
  for (int i = 0; i < 10; ++i) { std::cout << array2[i] << " "; }
  std::cout << "\n";

  std::pair<size_t, size_t> size_range = std::make_pair(0, 100);
  std::pair<const double &, const double &> value_range = std::make_pair(1.1, 200.3);
  zuo::SortAlgorithmTest<double>::Test(200, size_range, value_range, SelectSort);
  return 0;
}
