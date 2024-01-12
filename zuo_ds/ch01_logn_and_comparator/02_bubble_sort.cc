#include <utility>
#include <iostream>
#include "algorithm_test.h"

template<typename T>
void static BubbleSort(T array[], size_t n) {
  if (!array || n < 2) return;

  size_t last_pos = n;
  for (size_t i = last_pos; i != 1; i = last_pos) {
    last_pos = 1;
    for (size_t j = 1; j != i; ++j) {
      if (array[j - 1] > array[j]) {
        std::swap(array[j - 1], array[j]);
        last_pos = j;
      }
    }
  }
}

int main() {
  std::pair<size_t, size_t> size_range = std::make_pair(0, 100);
  std::pair<const double &, const double &> value_range = std::make_pair(1.1, 200.3);
  zuo::SortAlgorithmTest<double>::Test(200, size_range, value_range, BubbleSort);
  return 0;
}