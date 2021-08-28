// PATB 1019 The Black Hole of Numbers 

#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
// 针对 <= 4 位数, 存放各个位数(至少为 4 位数)
void Int2Vector(int number, vector<int> &vec) {
  if (number < 1000) vec.push_back(0);
  if (number < 100) vec.push_back(0);
  if (number < 10) vec.push_back(0); 
  while (number) {
    vec.push_back(number % 10);
    number /= 10;
  }
}

int Vector2Int(const vector<int> &vec) {
  int number = 0;
  for (int item : vec) {
    number = number * 10 + item;
  }
  return number;
}

int main() {

  int number, max, min, result;
  vector<int> vec;
  scanf("%d", &number);

  auto increase_sort = 
      [](const int &lhs, const int &rhs){ return lhs < rhs; };
  auto decrease_sort = 
      [](const int &lhs, const int &rhs){ return rhs < lhs; };

  while (true) {
    vec.clear();
    Int2Vector(number, vec);
    sort(vec.begin(), vec.end(), increase_sort);
    min = Vector2Int(vec);
    sort(vec.begin(), vec.end(), decrease_sort);
    max = Vector2Int(vec);
    result = max - min;
    printf("%04d - %04d = %04d", max, min, result);
    if ((result == 0) || (result == 6174)) {
      break;
    } else {
      printf("\n");
      number = result;
    }
  }
  return 0;
}