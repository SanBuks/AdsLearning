#include <utility>
#include <iostream>

template<typename T>
void static SelectSort(T array[], size_t n) {
  if (!array || n < 2) return;

  size_t min_index;
  for (size_t i = 0; i < n; ++i) {
    min_index = i;
    for (size_t j = i + 1; j < n; ++j) {
      min_index = array[j] < array[min_index] ? j : min_index;
    }
    std::swap(array[i], array[min_index]);
  }
}

int main() {
  int array[8] = {2, 1, 0, -1, 6, 9, 7, 0};
  SelectSort(array, 8);
//  int array[2] = {2, 1};
//  SelectSort(array, 2);
  for (int i : array) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  return 0;
}