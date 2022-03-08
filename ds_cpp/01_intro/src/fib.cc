#include "fib.h"

//  Fib 数列
//  -1  1  0  1  1  2  3  5  8 13 21 34 数值
//  -3 -2 -1  0  1  2  3  4  5  6  7  8 下标(从 0 开始)

namespace ds_cpp {

Fib::Fib(unsigned long long n) : n_(0ULL), p_(1ULL) {
  // 处理 Fib(0) = 1;
  n = !n ? 1 : n;
  while (n_ < n) {
    Next();
  }
}

unsigned long long Fib::Next() {
  // 没有溢出上限
  if (n_ + p_ >= n_) {
    n_ = p_ + n_;
    p_ = n_ - p_;
    return n_;
  } else {
    throw std::runtime_error("Fib::Next(): MAX Over Flow!");
  }
}

unsigned long long Fib::Prev() {
  // 没有溢出下限
  if (n_ - p_ <= p_ ) {
    p_ = n_ - p_;
    n_ = n_ - p_;
    return n_;
  } else {
    throw std::runtime_error("Fib::Prev(): Over Flow!");
  }
}

unsigned long long Fib::FibA(unsigned n) {
  if (n == 0) {
    return 0;
  } else if(n == 1 || n == 2) {
    return 1;
  } else {
    return FibA(n - 1) + FibA(n - 2);
  }
}

unsigned long long Fib::FibB(unsigned n, unsigned long long &pre) {
  if (n == 0) {
    pre = 1;
    return 0;
  } else {
    unsigned long long prepre;
    pre = FibB(n - 1, prepre);
    return pre + prepre;
  }
}

}