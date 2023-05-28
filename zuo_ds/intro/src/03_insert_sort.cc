#include <utility>
#include <vector>
#include <iostream>

template<typename T>
void static InsertSort(T array[], size_t n) {
  if (n < 2) return;

  for (size_t i = 1; i < n; ++i) {
    T temp = array[i];
    size_t index = i;
    for (size_t j = i; j > 0 && array[j - 1] > temp; --j) {
      array[j] = array[index = j - 1];
    }
    array[index] = temp;
  }
}



int main() {
  int array[8] = {2, 1, 0, -1, 6, 9, 7, 0};
  InsertSort(array, 8);
//  int array[2] = {2, 1};
//  InsertSort(array, 2);
  for (int i : array) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  return 0;
}
