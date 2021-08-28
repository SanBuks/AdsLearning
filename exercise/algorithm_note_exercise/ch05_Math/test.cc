#include <stdio.h>
#include <exception>
#include "gcd.h"
#include "fraction.h"

using namespace ::exercise::math;

void TestGcd();
void TestFraction();

int main() {
  TestGcd();
  TestFraction();
  return 0;
}

void TestGcd() {
  int a = 7, b = 6;
  const char *show_template = "gcd(%d, %d) = %d\n";
  printf(show_template, a, b, GcdCn(a, b));
}

void TestFraction() {
  try {
    Fraction f_exception(1, 0);
  } catch (std::exception &ex) {
    printf("%s\n", ex.what());
  }

  Fraction f1(7, 6);
  printf("f1 : ");
  f1.Show();
  putchar('\n');

  Fraction f2(12, 6);
  printf("f2 : ");
  f2.Show();
  putchar('\n');

  Fraction f3(3, 4);
  printf("f3 : ");
  f3.Show();
  putchar('\n');

  f1 = f1 + f2;
  printf("f1 + f2 = ");
  f1.Show();
  putchar('\n');

  f1 = f1 - f2;
  printf("f1 - f2 = ");
  f1.Show();
  putchar('\n');

  f2 = f2 * f3;
  printf("f1 * f2 = ");
  f2.Show();
  putchar('\n');

  f2 = f2 / f3;
  printf("f1 / f2 = ");
  f2.Show();
  putchar('\n');

}
