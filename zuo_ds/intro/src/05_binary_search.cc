#include <vector>
#include <iostream>

/// 二分并不需要输入数据是有序的, 只要数据满足二分排他性就可以使用二分

/// 返回 需要插入位置的下标
template<typename T, typename I>
size_t static BinarySearch(T &array, size_t n, const I &target) {
  size_t lo = 0;
  size_t hi = n;
  size_t mi = 0;
  while(lo < hi) {
    mi = lo + (hi - lo) / 2;
    if (array[mi] <= target) {
      lo = mi + 1;
    } else {
      hi = mi;
    }
  }
  return lo;
}

int main() {
  std::vector<int> vec {1};
//  std::vector<int> vec {1, 2, 3, 3, 8};
  std::cout << BinarySearch(vec, vec.size(), 0);
}
