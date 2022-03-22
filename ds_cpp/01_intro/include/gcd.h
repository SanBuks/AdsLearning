#ifndef DS_CPP_INTRO_GCD_H
#define DS_CPP_INTRO_GCD_H

#include <utility>

namespace ds_cpp {

namespace gcd {

/**
 *  欧几里得辗转相除法 求最大公约数
 *  a = kb + r, 设 d 是 a 和 b 的公约数
 *  r = a - kb, d 也是 r 的约数, 所有 a, b 的公约数都是 b, a % b 的公约数
 */
unsigned long GcdEn(unsigned long a, unsigned long b) {
  if (b > a) {
    std::swap(a, b);
  }
  while (b) {
    auto temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

/**
 *  中华更相减损术 O(log2(a+b))
 *  r = a - b, 设 d 是 a 和 b 的公约数
 *  d 也是 r 的约数, 所有 a, b 的公约数都是 b, a - b 的公约数
 */
unsigned long GcdCnOrigin(unsigned long a, unsigned long b) {
  if (b > a) {
    std::swap(a, b);
  }
  while (b) {
    auto temp = a - b;
    if (temp > b) {
      a = temp;
    } else {
      a = b;
      b = temp;
    }
  }
  return a;
}

/**
 *  中华更相减损术 对 2 因子优化, 有助于底层运算
 */
unsigned long GcdCn(unsigned long a, unsigned long b) {
  if (a == 0 || b == 0) {
    return a == 0 ? b : a;
  }

  unsigned long p = 0;
  while (!(a & 1) && !(b & 1)) {
    a >>= 1;
    b >>= 1;
    ++p;
  }

  while (true) {
    while (!(a & 1)) {
      a >>= 1;
    }
    while (!(b & 1)) {
      b >>= 1;
    }

    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }

    if (a == 0) {
      return b << p;
    }
    if (b == 0) {
      return a << p;
    }
  }
}

/**
 *  最大公倍数
 */
unsigned long Lcm(unsigned long a, unsigned long b) {
  return a / GcdCn(a, b) * b;
}

}  // namespace ds_cpp::gcd

}  // namespace ds_cpp

#endif
