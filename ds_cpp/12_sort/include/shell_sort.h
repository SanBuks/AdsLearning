#ifndef DS_CPP_SHELL_SORT_H_
#define DS_CPP_SHELL_SORT_H_

namespace ds_cpp {

/**
 * 希尔排序
 * 本质是 分组插入排序
 * 平均时间复杂度 O(n^(3/2))
 *
 * 糟糕情况 2^n 个元素分半交错
 * 导致分组无效, 泾渭分明, gap 尽量要使得
 * 举例 [0-3] 与 [3-7] 交错排列 O(n^2)
 *
 * 邮资问题
 * g, h 的线性组合为能够表示的邮资
 * N(g, h), X(g, h) = Max(N(g,h)) = gh - g - h
 *
 * h-sorting 转为矩阵后进行列排序
 * h-sorted | g-sorted = (mg + nh) ordered, 0-X(g,h) 存在 逆序对
 * 逆序对减少后使用插入排序较为契合
 */
template<typename T>
int ShellSort(T array[], size_t len) {
  if (!array) {
    return -1;
  }
  if (len == 0) {
    return 1;
  }

  size_t prev = 0, cur = 0;
  // 遍历 gap 为 1 为止
  for (size_t gap = len / 2; gap >= 1; gap /= 2) {
    //  顺序遍历每个组, 从每组第二个及之后的元素开始用插入排序
    for (prev = gap; prev < len; ++prev) {
      // 要插入的值
      T temp = array[prev];
      // 插入边界
      cur = prev;
      while (cur >= gap) {        // 左边还有元素
        cur -= gap;               // 指向该元素
        if (array[cur] > temp) {  // 整体往右移
          array[cur + gap] = array[cur];
        } else {
          cur += gap;             // 已经排序好, 右边则是插入地方
          break;
        }
      }
      array[cur] = temp;
    }
  }
  return 1;
}

}

#endif
