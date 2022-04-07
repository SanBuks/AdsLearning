#ifndef DS_CPP_CONVERSION_H
#define DS_CPP_CONVERSION_H

#include "stack.h"

#include <iostream>

namespace ds_cpp {

namespace conversion {

// 将 n 十进制转换为 base 进制, 输出到 os 中
void Convert(std::ostream &os, long long n, int base) {
  static const char OP[] =
      {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
       'A', 'B', 'C', 'D', 'E', 'F'};

  // base 范围 [2,16]
  if (base < 2 || base > 16)  {
    return;
  }

  bool negative = n < 0;
  n = negative ? -n : n;

  Stack<char> s;
  while (0 < n) {
    s.Push(OP[n % base]);
    n /= base;
  }

  if (negative) {
    os << "-";
  }

  while (!s.Empty()) {
    os << s.Pop();
  }
}

}  // namespace ds_cpp::conversion

}  // namespace ds_cpp

#endif