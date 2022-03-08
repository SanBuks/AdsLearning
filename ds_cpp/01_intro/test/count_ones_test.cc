#include "count_ones.h"

#include <gtest/gtest.h>
#define GTEST_COUT std::cout << "[---INFO---] "

// __builtin_popcount() 是 gcc 自带函数, 用于测试用例

class TestCountOnes: public ::testing::Test {
 protected:
  unsigned int number1 = 0;            //  0
  unsigned int number2 = -1U;          // 32
  // 1101 0011 1010 0101 1001 0110 1100 1011
  unsigned int number3 = 0xD3A596CBU;  // 18
};

TEST_F(TestCountOnes, CountOnesATest) {
  using namespace ds_cpp::count_ones;

  auto left = CountOnesA(number1);
  auto right = __builtin_popcount(number1);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right);

  left = CountOnesA(number2);

  right = __builtin_popcount(number2);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right) << left;

  left = CountOnesA(number3);
  right = __builtin_popcount(number3);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right) << left;
}

TEST_F(TestCountOnes, CountOnesBTest) {
  using namespace ds_cpp::count_ones;

  auto left = CountOnesB(number1);
  auto right = __builtin_popcount(number1);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right);

  left = CountOnesB(number2);
  right = __builtin_popcount(number2);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right) << left;

  left = CountOnesB(number3);
  right = __builtin_popcount(number3);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right) << left;
}

TEST_F(TestCountOnes, CountOnesCTest) {
  using namespace ds_cpp::count_ones;

  auto left = CountOnesC(number1);
  auto right = __builtin_popcount(number1);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right);

  left = CountOnesC(number2);
  right = __builtin_popcount(number2);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right) << left;

  left = CountOnesC(number3);
  right = __builtin_popcount(number3);
  GTEST_COUT << left << "\n";
  ASSERT_EQ(left, right) << left;
}