#ifndef DS_CPP_INTRO_COUNT_ONES_H
#define DS_CPP_INTRO_COUNT_ONES_H

// 计算数值中二进制 1 的个数
// leetcode 0338
// leetcode 0191

namespace ds_cpp {

namespace count_ones {

/**
  * 计算数值中二进制 1 的个数 O(logn)
  * 若使用 有符号数则先转换成对应大小的无符号数再调用函数, 如
  * int a = 1; CountOneX(static_cast<unsigned>(a));
  * 否则, 先转换为 long long 再转换为 unsigned long long 会出现错误
  */
int CountOnesA(unsigned long long number) {
  int sum = 0;
  while (number) {
    sum += (number & 1ULL) ? 1 : 0;
    number >>= 1ULL;
  }
  return sum;
}

/**
  * 计算数值中二进制 1 的个数 O(r), r 为 实际 1 的个数
  */
int CountOnesB(unsigned long long number) {
  int sum = 0;
  while (number) {
    ++sum;
    number &= (number - 1ULL);  // 相当于把最后一个 1 去除
  }
  return sum;
}

/**
 *  计算 2^n
 */
unsigned long long inline Pow(unsigned long long number) {
  return 1ULL << number;
}
/**
 * 生成对应掩码, 分组长度 为 2^number
 * 1) 掩码定义与分组长度
 * 返回对应的 0/1 交互的掩码(高位从 0 开始), 其中 0/1 连续的长度定义为分组长度, 如
 * 0000111100001111 是分组长度为 4 的掩码
 * 2) 生成规则
 * Mask(0): -1 / 11b    = 01010101b 分组长度为 2^0 = 1
 * Mask(1): -1 / 101b   = 00110011b 分组长度为 2^1 = 2
 * Mask(2): -1 / 10001b = 00001111b 分组长度为 2^2 = 4
 * Mask(x): -1 / 10b    = error 对特殊情况做特殊处理 10b => 1b
 */
unsigned long long Mask(unsigned number) {
  auto divider = Pow(Pow(number));
  // 对特殊情况做特殊处理 10b => 1b
  if (divider == 1UL) {
    divider = 0;
  }
  return -1ULL / (divider + 1);
}

/**
 * 以 2^group_length_ex 分组 计算各组类的 1 的个数
 * 1) 第一步
 * 1111 & 0101 = 0101 mask 出 1 组中 1 的位  1111 >> 1 = 0111
 * 0111 & 0101 = 0101 mask 出 0 组中 1 的位
 * 0101 + 0101 = 1010 得出 前 0/1 组中 1 的个数 和 后 0/1 组中 1 的个数
 * 2) 第二步
 * 1010 & 0011 = 0010 mask 出 1 组中 1 的位 1010 >> 2 = 0010
 * 0010 & 0011 = 0010 mask 出 0 组中 1 的位
 * 0010 + 0010 = 0100 得出 前 0/1 组中 1 的个数 和 后 0/1 组中 1 的个数
 */
unsigned long long Round(unsigned long long number, unsigned group_length_ex) {
  return (number & Mask(group_length_ex)) +
         (number >> Pow(group_length_ex) & Mask(group_length_ex));
}

/**
 * @return log2(sizeof(Type) * 8))
 */
template<typename T>
unsigned LogBitLength() {
  unsigned num = sizeof(T) * 8;
  unsigned result = 0;
  while (num > 1) {
    ++result;
    num >>= 1;
  }
  return result;
}

/**
 * 迭代计算 1 的个数 O(log(log(n)))
 */
unsigned CountOnesC(unsigned long long number) {
  unsigned max = LogBitLength<unsigned long long>();
  for (unsigned group_length_ex = 0; group_length_ex != max; ++group_length_ex) {
    number = Round(number, group_length_ex);
  }
  return static_cast<unsigned>(number);
}

} // namespace ds_cpp::count_ones

} // namespace ds_cpp

#endif