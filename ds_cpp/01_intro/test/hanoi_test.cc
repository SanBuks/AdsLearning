#include "hanoi.h"

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

TEST(TestHanoiSubSet, HanoiTest) {
  using namespace ds_cpp::hanoi;
  hanoi(4, 'A', 'T', 'B');
}

