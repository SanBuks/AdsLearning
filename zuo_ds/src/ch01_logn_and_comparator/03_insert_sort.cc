#include <utility>
#include <iostream>
#include "comparator.h"

template<typename T>
void static InsertSort(T array[], size_t n) {
  if (!array || n < 2) return;

  for (size_t i = 1; i != n; ++i) {
    auto insert_one = array[i];
    size_t swap_index = i;
    for (size_t j = i; j > 0 && array[j - 1] > insert_one; --j) {
      swap_index = j - 1;
      array[j] = array[j - 1];
    }
    array[swap_index] = insert_one;
  }
}

int main() {
  std::pair<size_t, size_t> size_range = std::make_pair(0, 100);
  std::pair<const double &, const double &> value_range = std::make_pair(1.1, 200.3);
  zuo::SortAlgorithmTest<double>::Test(200, size_range, value_range, InsertSort);
  return 0;
}
