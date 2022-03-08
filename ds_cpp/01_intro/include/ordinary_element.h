#ifndef DS_CPP_INTRO_ORDINARY_ELEMENT_H
#define DS_CPP_INTRO_ORDINARY_ELEMENT_H

#include "bubble_sort.h"

namespace ds_cpp {

namespace ordinary_element {

 /**
  * 获取平凡元素(非最大和最小) 就地算法 O(1)
  * @param array 数组
  * @param n 数组大小
  * @param p_target 指向目标对象指针
  * @return -1 失败, 0 成功
  */
template<typename T>
int OrdinaryElement(T array[], std::size_t n, T **p_target) {
  if (n < 3) {
    *p_target = nullptr;
    return -1;
  }
  bubble_sort::BubbleSortA(array, 3);
  *p_target = &array[1];
  return 0;
}

}  // namespace ordinary_element

}  // namespace ds_cpp

#endif