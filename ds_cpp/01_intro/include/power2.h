#ifndef DS_CPP_INTRO_POWER2_H
#define DS_CPP_INTRO_POWER2_H

#include <cmath>

// 计算 2^n, x^n
// leetcode 0050

namespace ds_cpp {

namespace power2 {

/**
 * 计算 2^n, O(n) = O(2^r)
 */
unsigned long long Power2A(std::size_t n) {
  auto result = 1ULL;
  while (n-- != 0) {
    result <<= 1;
  }
  return result;
}

/**
 * 计算 2^n, O(logn) = O(r)
 * 推导过程:
 * 2^(2^n) = (((2^2)^2)^2).... (n个)
 * 2^1111 = 2^(2^3)        * 2^(2^2)   * 2^(2^1) * 2^(2^0) 二进制加权公式
 *        = ((2^2)^2)^2    * (2^2)^2   * (2)^2   * 2       公式推导
 *        = (((2^2)^2)     * (2^2)     * (2))^2  * 2       一步一步提取 ^2
 *        = (((2^2         * 2)^2      * 2)^2    * 2       一步一步提取 ^2
 *        = ((((1 * 2)^2   * 2)^2      * 2)^2    * 2       得到递推形式
 * 2^abcd = ((((1 * 2^a)^2 * 2^b)^2    * 2^c)^2  * 2^d     推广
 * 2^n_k  = (2^n_(k-1))^2  * 2^bk                          最后得到递推公式
 */
unsigned long long Power2B(std::size_t n) {
  if (!n) {
    return 1;
  }
  unsigned long long temp = Power2B(n >> 1);
  return (temp * temp) << (n & 1 ? 1 : 0);
}

/**
 * 计算 2^n, O(logn) = O(r)
 * 上述递归的迭代版本
 */
unsigned long long Power2C(std::size_t n) {
  unsigned long long result = 1;
  unsigned long long multiplier = 2;
  while (n) {
    if (n & 1ULL) {
      result *= multiplier;
    }
    multiplier *= multiplier;
    n >>= 1ULL;
  }
  return result;
}

/**
 * 计算 base^n, O(logn) = O(r)
 * 上述的推广版本
 */
unsigned long long PowerN(std::size_t base, std::size_t n) {
  if (base == 0) {
    return 0ULL;
  }
  unsigned long long result = 1;
  unsigned long long multiplier = base;
  while (n) {
    if (n & 1) {
      result *= multiplier;
    }
    multiplier *= multiplier;
    n >>= 1;
  }
  return result;
}

}  // namespace ds_cpp::power2

}  // namespace ds_cpp

#endif