#ifndef DS_CPP_INTRO_HANOI_H
#define DS_CPP_INTRO_HANOI_H

#include <iostream>

namespace ds_cpp {

namespace hanoi {

/**
 * 打印移动过程
 * @param source 原柱子 字符
 * @param target 目标柱子 字符
 */
void move(char source, char target) {
  std::cout << source << " ---> " << target << "\n";
}

/**
 * 递归打印 汉诺塔问题 过程 O(2^n)
 * @param n source 上有 n 个盘子
 * @param source 原柱子 字符
 * @param temp 临时柱子 字符
 * @param target 目标柱子 字符
 */
void hanoi(int n, char source, char temp, char target) {
  if(n > 0) {
    hanoi(n-1, source, target, temp);
    move(source, target);
    hanoi(n-1, temp, source, target);
  }
}

}  // namespace ds_cpp::hanoi

}  // namespace ds_cpp

#endif
