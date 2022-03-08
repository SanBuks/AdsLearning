#include "bubble_sort.h"

#include <gtest/gtest.h>
#define GTEST_COUT std::cout << "[---INFO---] "

class TestBubbleSort : public ::testing::Test {
 protected:
  void TearDown() override {
    delete [] array3;
    delete [] array2;
    delete [] array1;
  }
  int *array1 = new int[0];
  int *array2 = new int[1]{3};
  int *array3 = new int[10]{3, 4, 5, 2, 1, 6, 9, 8, 7, 0};
};

TEST_F(TestBubbleSort, BubbleSortATest) {
  using namespace ::ds_cpp::bubble_sort;
  BubbleSortA(array1, 0);
  BubbleSortA(array2, 1);
  BubbleSortA(array3, 10);
  ASSERT_EQ(array2[0], 3);
  for (std::size_t i = 0; i != 10; ++i) {
    ASSERT_EQ(array3[i], i);
  }
}

TEST_F(TestBubbleSort, BubbleSortBTest) {
  using namespace ::ds_cpp::bubble_sort;
  BubbleSortB(array1, 0);
  BubbleSortB(array2, 1);
  BubbleSortB(array3, 10);
  ASSERT_EQ(array2[0], 3);
  for (std::size_t i = 0; i != 10; ++i) {
    ASSERT_EQ(array3[i], i);
  }
}

TEST_F(TestBubbleSort, BubbleSortCTest) {
  using namespace ::ds_cpp::bubble_sort;
  BubbleSortC(array1, 0);
  BubbleSortC(array2, 1);
  BubbleSortC(array3, 10);
  ASSERT_EQ(array2[0], 3);
  for (std::size_t i = 0; i != 10; ++i) {
    ASSERT_EQ(array3[i], i);
  }
}