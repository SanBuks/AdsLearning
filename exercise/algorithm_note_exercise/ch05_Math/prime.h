#ifndef CH05_MATH_PRIME_H
#define CH05_MATH_PRIME_H

namespace exercise {
namespace math {

// 1. 判断是否素数 为通过 根号 筛选
// n/k * k == n
bool IsPrime(int n) {
  if (n <= 1) {
    return false;
  }
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

// 2.

}
}

#endif