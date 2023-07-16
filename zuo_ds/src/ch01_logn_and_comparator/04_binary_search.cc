#include <vector>
#include <iostream>

/// 返回 upper_bound
template<typename T, typename I>
size_t static BinarySearch(T &array, size_t n, const I &target) {
  size_t lo = 0;
  size_t hi = n;
  size_t mi = 0;
  while(lo < hi) {
    mi = lo + (hi - lo) / 2;
    // [e1, e2, e3 <= target, e4 > target, e5, e6 ... }
    if (array[mi] <= target) {
      lo = mi + 1;
    } else {
      hi = mi;
    }
  }
  return lo;
}

int main() {
//  std::vector<int> vec {1};
  std::vector<int> vec {1, 2, 3, 3, 8};
  std::cout << BinarySearch(vec, vec.size(), 3);
}
