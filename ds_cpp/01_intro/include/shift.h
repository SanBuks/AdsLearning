#ifndef DS_CPP_INTRO_SHIFT_H
#define DS_CPP_INTRO_SHIFT_H

#include <cstddef>
#include <stdexcept>

namespace ds_cpp {

namespace shift {

/**
 * 倒转 [lo, hi) 区间
 */
template <typename T>
void Reverse(T array[], size_t lo, size_t hi) {
  while (lo < hi) {
    T tmp = array[lo];
    array[lo] = array[hi - 1];
    array[hi - 1] = tmp;
    ++lo; --hi;
  }
}

/**
 * 在 [lo, hi) 区间左循环移位 n 位
 */
template <typename T>
void LShift(T array[], size_t n, size_t lo, size_t hi) {
  if (hi > lo) {
    n %= hi - lo;
    Reverse(array, lo, lo + n);
    Reverse(array, lo + n, hi);
    Reverse(array, 0, hi);
  }
}

/**
 * 在 [lo, hi) 区间右循环移位 n 位
 */
template <typename T>
void RShift(T array[], size_t n, size_t lo, size_t hi) {
  if (hi > lo) {
    n %= hi - lo;
    Reverse(array, hi - n, hi);
    Reverse(array, lo, hi - n);
    Reverse(array, 0, hi);
  }
}

/**
 * 从 array[s] 出发, 以 pos , pos + k 间隔循环左移
 * O(n / gcd(n, k)) 如果 n, k 互素 则循环 n 次 (k < n)
 *                  如果 n, k 不互素 则循环同余类中的个数
 * 返回移动次数
 */
template <typename T>
size_t LShiftInterval(T array[], size_t n, size_t s, size_t k) {
  if (n == 0 || s >= n) {
    throw std::runtime_error("ShiftMod(): Parameter Invalid!");
  }
  size_t move = 0;
  T backup = array[s];
  size_t i = s, j = (s + k) % n;  // i 待复制的位置, j 待移动的位置
  while (s != j) {
    array[i] = array[j];
    i = j;
    j = (j + k) % n;
    ++move;
  }
  array[i] = backup;
  return move + 1;
}

/**
 * 在 [lo, hi) 区间左循环移位 n 位, 缓存不友好型
 */
template <typename T>
void LShiftMod(T array[], size_t n, size_t lo, size_t hi) {
  if (hi > lo) {
    n %= hi - lo;
    size_t move = 0, s = 0;
    while (move < hi - lo) {
      move += LShiftInterval(array + lo, hi - lo, s++, n);
    }
  }
}

}  // namespace ds_cpp::shift

}  // namespace ds_cpp

#endif
