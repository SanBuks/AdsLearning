#include "gcd.h"

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "


TEST(TestGcd, GcdCnTest) {
  using namespace ds_cpp::gcd;

  ASSERT_EQ(GcdCn(0, 0), 0);
  ASSERT_EQ(GcdCn(0, 100), 100);
  ASSERT_EQ(GcdCn(21, 3), 3);
  ASSERT_EQ(GcdCn(21, 4), 1);
}

TEST(TestGcd, GcdCnOriginTest) {
  using namespace ds_cpp::gcd;

  ASSERT_EQ(GcdCnOrigin(0, 0), 0);
  ASSERT_EQ(GcdCnOrigin(0, 100), 100);
  ASSERT_EQ(GcdCnOrigin(21, 3), 3);
  ASSERT_EQ(GcdCnOrigin(21, 4), 1);
}

TEST(TestGcd, GcdEnTest) {
  using namespace ds_cpp::gcd;

  ASSERT_EQ(GcdEn(0, 0), 0);
  ASSERT_EQ(GcdEn(0, 100), 100);
  ASSERT_EQ(GcdEn(21, 3), 3);
  ASSERT_EQ(GcdEn(21, 4), 1);
}