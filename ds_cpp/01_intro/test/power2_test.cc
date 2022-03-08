#include "power2.h"

#include <gtest/gtest.h>
#define GTEST_COUT std::cout << "[---INFO---] "

class TestPower2: public ::testing::Test {
 protected:
  std::size_t number1 = 0U;
  std::size_t number2 = 1U;
  std::size_t number3 = 4U;
  std::size_t number4 = 63U;

  unsigned long long target_number1 = 1ULL;
  unsigned long long target_number2 = 2ULL;
  unsigned long long target_number3 = 16ULL;
  unsigned long long target_number4 = 9223372036854775808ULL;
};

TEST_F(TestPower2, Power2ATest) {
  using namespace ds_cpp::power2;

  auto number = Power2A(number1);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number1);

  number = Power2A(number2);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number2);

  number = Power2A(number3);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number3);

  number = Power2A(number4);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number4);
}

TEST_F(TestPower2, Power2BTest) {
  using namespace ds_cpp::power2;

  auto number = Power2B(number1);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number1);

  number = Power2B(number2);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number2);

  number = Power2B(number3);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number3);

  number = Power2B(number4);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number4);
}

TEST_F(TestPower2, Power2CTest) {
  using namespace ds_cpp::power2;

  auto number = Power2C(number1);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number1);

  number = Power2C(number2);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number2);

  number = Power2C(number3);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number3);

  number = Power2C(number4);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number4);
}

class TestPowerN: public ::testing::Test {
 protected:
  std::pair<size_t, size_t> number1{0U, 3U};
  std::pair<size_t, size_t> number2{2U, 3U};
  std::pair<size_t, size_t> number3{9U, 10U};
  std::pair<size_t, size_t> number4{6U, 4U};

  unsigned long long target_number1 = 0ULL;
  unsigned long long target_number2 = 8ULL;
  unsigned long long target_number3 = 3486784401ULL;
  unsigned long long target_number4 = 1296ULL;
};

TEST_F(TestPowerN, PowerNTest) {
  using namespace ds_cpp::power2;

  auto number = PowerN(number1.first, number1.second);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number1);

  number = PowerN(number2.first, number2.second);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number2);

  number = PowerN(number3.first, number3.second);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number3);

  number = PowerN(number4.first, number4.second);
  GTEST_COUT << number << "\n";
  ASSERT_EQ(number, target_number4);
}