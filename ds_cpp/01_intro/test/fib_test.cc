#include "fib.h"

#include "gtest/gtest.h"
#define GTEST_COUT std::cout << "[---INFO---] "

TEST(TestFib, FibTest) {
  using namespace ds_cpp;

  Fib fib1(0);
  ASSERT_EQ(fib1.Get(), 1ULL);
  ASSERT_EQ(fib1.Next(), 1ULL);

  Fib fib2(33);
  ASSERT_EQ(fib2.Prev(), 21);

  Fib min_overflow(0);
  ASSERT_THROW(min_overflow.Prev(), std::runtime_error);

  // 64 位机器
  // 7540113804746346429 + 12200160415121876738 =
  // 19740274219868223167 > 18446744073709551615 (2^64-1)
  ASSERT_THROW(Fib(12200160415121876738ULL + 1), std::runtime_error);


  ASSERT_EQ(Fib::FibA(0), 0);
  ASSERT_EQ(Fib::FibA(1), 1);
  ASSERT_EQ(Fib::FibA(7), 13);

  unsigned long long NON;
  ASSERT_EQ(Fib::FibB(0, NON), 0);
  ASSERT_EQ(Fib::FibB(1, NON), 1);
  ASSERT_EQ(Fib::FibB(7, NON), 13);

}