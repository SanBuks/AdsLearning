#ifndef DS_CPP_INTRO_BUBBLE_SORT_H
#define DS_CPP_INTRO_BUBBLE_SORT_H

#include <utility>

// 1. 算法的基本要素(特性):
//   1) 输入
//   2) 输出
//   3) 确定性
//   4) 可行性
//   5) 有穷性 (涉及到问题的可计算性)
//
// 2. 算法的其他评价标准:
//   1) 正确性, 对多种输入规模, 总能得出预期结果
//   2) 高效型, 时间复杂度和空间复杂度低 (涉及到难解性问题)
//   3) 健壮性, 可以面对多种退化情况
//   4) 可读性, 程序内容容易理解
//   5) 拓展性, 可以重用
//
// 3. 三种冒泡排序

namespace ds_cpp {

namespace bubble_sort {

/**
 * BubbleSortA O(n^2): 纯粹计算次数, 不考虑数组的某一段是否已排序
 */
template<typename T>
void BubbleSortA(T array[], std::size_t n) {
  // n = 0, n - 1 主循环溢出, 需要考虑退化条件
  if (n < 2) {
    return ;
  }
  for (std::size_t i = 0; i < n - 1; ++i) {
    for (std::size_t j = 1; j < n - i; ++j) {
      if (array[j - 1] > array[j]) {
        std::swap(array[j - 1], array[j]);
      }
    }
  }
}

/**
 * BubbleSortB O(n^2): 利用标志符提前判断是否已排序, 但只能优化已排序的最后区间
 */
template<typename T>
void BubbleSortB(T array[], std::size_t n) {
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (std::size_t i = 1; i < n; ++i) {
      if (array[i - 1] > array[i]) {
        std::swap(array[i - 1], array[i]);
        sorted = false;
      }
    }
    --n;
  }
}

/**
 * BubbleSortC O(n^2): 记录最后已排序位置, 可以优化已排序的多个区间
 */
template<typename T>
void BubbleSortC(T array[], std::size_t n) {
  std::size_t last_swap_pos = n;  // 指向尾后
  for (std::size_t i = last_swap_pos; i != 1; i = last_swap_pos) {
    last_swap_pos = 1;
    for (std::size_t j = 1; j < i; ++j) {
      if (array[j - 1] > array[j]) {
        std::swap(array[j - 1], array[j]);
        last_swap_pos = j;
      }
    }
  }
}

}  // namespace ds_cpp::bubble_sort

}  // namespace ds_cpp

#endif