#ifndef DS_CPP_INTRO_FIB_H
#define DS_CPP_INTRO_FIB_H

#include <stdexcept>

namespace ds_cpp {

/**
 * Fib 数列类超出 上限 或 下限会抛出异常
 */
class Fib {
 public:
  /**
   * 最常见的递归求解 Fib[n]
   */
  static unsigned long long FibA(unsigned n);
  /**
   * 状态转移递归求解 Fib[n]
   */
  static unsigned long long FibB(unsigned n, unsigned long long &pre);

  /**
   * 获取不小于 n 的最小项 Fib 数
   */
  explicit Fib(unsigned long long n);
  /**
   * 获取当前 Fib 数
   */
  unsigned long long Get() const { return n_; };
  /**
   * 获取下一个 Fib 数
   */
  unsigned long long Next();
  /**
   * 获取前一个 Fib 数
   */
  unsigned long long Prev();
 private:
  unsigned long long n_; // 当前数
  unsigned long long p_; // 前一个数
};

}  // namespace ds_cpp

#endif