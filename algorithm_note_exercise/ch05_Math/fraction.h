#ifndef CH05_MATH_FRACTION_H
#define CH05_MATH_FRACTION_H
#include <stdio.h>
#include <utility>
#include <iostream>
#include <exception>
#include <cmath>

#include "gcd.h"

namespace exercise {
namespace math {

class Fraction {
public:
  Fraction(int up, int down);
  Fraction(const Fraction & rhs);
  int down() { return down_; }
  int up() { return up_; }
  void set_down(int down) { down_ = down; }
  void set_up(int up) { up_ = up; }

  /**
   * 约分, 始终以分子为有符号数
   */
  Fraction &Reduction();
  Fraction &operator=(const Fraction &rhs);
  Fraction &operator+(const Fraction &rhs);
  Fraction &operator-(const Fraction &rhs);
  Fraction &operator*(const Fraction &rhs);
  Fraction &operator/(const Fraction &rhs);
  void Show();

private:
  int up_;
  int down_;
};

Fraction &Fraction::operator=(const Fraction &rhs) {
  up_ = rhs.up_;
  down_ = rhs.down_;
  return *this;
}

Fraction::Fraction(int up, int down) : up_(up), down_(down) {
  if (down_ == 0) {
    throw std::runtime_error("Denominator Can't Be 0 !");
  }
} 
Fraction::Fraction(const Fraction & rhs) : up_(rhs.up_), down_(rhs.down_) { }

Fraction &Fraction::Reduction() {
  if (down_ < 0) {
    up_ = -up_;
    down_ = -down_;
  }
  if (up_ == 0) {
    down_ = 1;
  } else {
    int d = GcdCn(up_, down_);
    up_ = up_ / d;
    down_ = down_ / d;
  }
  return *this;
}

Fraction &Fraction::operator+(const Fraction &rhs) {
  up_ = up_ * rhs.down_ + down_ * rhs.up_;
  down_ = down_ * rhs.down_;
  return Reduction();
}

Fraction &Fraction::operator-(const Fraction &rhs) {
  up_ = up_ * rhs.down_ - down_ * rhs.up_;
  down_ = down_ * rhs.down_;
  return Reduction();
}

Fraction &Fraction::operator*(const Fraction &rhs) {
  up_ = up_ * rhs.up_;
  down_ = down_ * rhs.down_;
  return Reduction();
}

Fraction &Fraction::operator/(const Fraction &rhs) {
  up_ = up_ * rhs.down_;
  down_ = down_ * rhs.up_;
  return Reduction();
}

void Fraction::Show() {
  Reduction();
  if (down_ == 1) {
    printf("%d", up_);
  } else if (std::abs(up_) > down_){
    printf("%d %d / %d", up_ / down_, up_ % down_, down_);
  } else {
    printf("%d / %d", up_, down_);
  }
}

}
}

#endif