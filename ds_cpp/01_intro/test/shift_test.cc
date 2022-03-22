#include "shift.h"

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

class TestShift: public ::testing::Test {
 protected:
  void TearDown() override {
    delete [] array3;
    delete [] array2;
    delete [] array1;
  }
  int *array1 = new int[0];
  int *array2 = new int[1]{1};
  int *array3 = new int[6]{1, 2, 3, 4, 5, 6};
};


TEST_F(TestShift, LShiftTest) {
  using namespace ds_cpp::shift;
  LShift(array1, 2, 0, 0);

  LShift(array2, 7, 0, 1);
  ASSERT_EQ(array2[0], 1);

  LShift(array3, 8, 0, 6);
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(array3[i], i + 3);
  }
  for (int i = 4; i < 6; ++i) {
    ASSERT_EQ(array3[i], i - 3);
  }
}

TEST_F(TestShift, RShiftTest) {
  using namespace ds_cpp::shift;
  RShift(array1, 2, 0, 0);

  RShift(array2, 7, 0, 1);
  ASSERT_EQ(array2[0], 1);

  RShift(array3, 8, 0, 6);
  for (int i = 2; i < 6; ++i) {
    ASSERT_EQ(array3[i], i - 1);
  }
  for (int i = 0; i < 2; ++i) {
    ASSERT_EQ(array3[i], i + 5);
  }
}

TEST_F(TestShift, LShiftModTest) {
  using namespace ds_cpp::shift;
  LShiftMod(array1, 2, 0, 0);

  LShiftMod(array2, 7, 0, 1);
  ASSERT_EQ(array2[0], 1);

  LShiftMod(array3, 8, 0, 6);
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(array3[i], i + 3);
  }
  for (int i = 4; i < 6; ++i) {
    ASSERT_EQ(array3[i], i - 3);
  }
}