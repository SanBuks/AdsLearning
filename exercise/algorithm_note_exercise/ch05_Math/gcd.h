#ifndef CH05_MATH_GCD_H
#define CH05_MATH_GCD_H
#include <utility>
namespace exercise {
namespace math {

// 1.1 欧几里得 递归版 最大公约数
// 默认 b < a
// b == a 在 return 时 等价为 gcd(b, 0)
// b >  a 在 return 时 等价为 gcd(b, a)
int GcdRecursive(int a, int b) {
  if (b == 0) return a;
  return GcdRecursive(b, a % b);
}

// 1.2 欧几里得 递归版 最大公约数
int GcdIterator(int a, int b) {
  if (b > a) std::swap(a, b);
  while (b) {
    int temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

// 2. 中华更相减损法 
int GcdCn(int a, int b) {
  // 2 的 公约数因子
  int p = 0;
  // 抽取 公约数的偶数因子 直到有一个为奇数为止
  if (!(a & 1) && !(b & 1)) {
    p += 1;
    a >>= 1;
    b >>= 1;
  }

  while (true) {
    // 一个 奇数 和 一个偶数的公约数因子不可能为 2
    // 抽取 其中的 偶数因子
    while (!(a & 1)) a >>= 1;
    while (!(b & 1)) b >>= 1;
    (a > b) ? a = a - b : b = b - a;
    if (a == 0) return b << p;
    if (b == 0) return a << p;
  }
}

// 3. 求最大公倍数
int Lcd(int a, int b) {
  return a / GcdCn(a, b) * b;
}

}
}
#endif