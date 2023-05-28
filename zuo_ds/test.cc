#include <cstddef>
#include <utility>

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