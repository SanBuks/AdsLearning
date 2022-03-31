#include "cycle_times.h"

#include "gtest/gtest.h"
#define GTEST_COUT std::cout << "[---INFO---] "

TEST(TestCycleTimes, CycleTimesTest) {
  using namespace ds_cpp::cycle_times;
  const unsigned n1 = 0;
  const unsigned n2 = 1;
  const unsigned n3 = 13;
  const unsigned n4 = 7007;

  EXPECT_EQ(F1(n1), F1Times(n1));
  EXPECT_EQ(F1(n2), F1Times(n2));
  EXPECT_EQ(F1(n3), F1Times(n3));
  EXPECT_EQ(F1(n4), F1Times(n4));

  EXPECT_EQ(F2(n1), F2Times(n1));
  EXPECT_EQ(F2(n2), F2Times(n2));
  EXPECT_EQ(F2(n3), F2Times(n3));
  EXPECT_EQ(F2(n4), F2Times(n4));

  EXPECT_EQ(F3(n1, 2022), F3Times(n1, 2022));
  EXPECT_EQ(F3(n2, 2022), F3Times(n2, 2022));
  EXPECT_EQ(F3(n3, 2022), F3Times(n3, 2022));
  EXPECT_EQ(F3(n4, 2022), F3Times(n4, 2022));

}
