#include <utility>
#include <iostream>

template<typename T>
void static BubbleSort(T array[], size_t n) {
  if (!array || n < 2) return;

  size_t last_pos = n;
  for (size_t i = last_pos; i > 1; i = last_pos) {
    last_pos = 1;
    for (size_t j = 1; j < i; ++j) {
      if (array[j - 1] > array[j]) {
        std::swap(array[j - 1], array[j]);
        last_pos = j;
      }
    }
  }
}

int main() {
  int array[8] = {2, 1, 0, -1, 6, 9, 7, 0};
  BubbleSort(array, 8);
//  int array[2] = {2, 1};
//  BubbleSort(array, 2);
  for (int i : array) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  return 0;
}
