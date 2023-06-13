#include <gtest/gtest.h>

#include "shell_sort.h"

#define GTEST_COUT std::cout << "[---INFO---] "

class TestShellSort : public ::testing::Test {
 protected:
  void TearDown() override {
    delete [] array2;
    delete [] array3;
  }
  int *array1 = nullptr;
  int *array2 = new int[1] {1};
  int *array3 = new int[10]{3, 4, 5, 2, 1, 6, 9, 8, 7, 0};
};

TEST_F(TestShellSort, ShellSortTest) {
  using namespace ds_cpp;
  ASSERT_EQ(ShellSort(array1, 1), -1);

  ShellSort(array2, 1);
  ASSERT_EQ(ShellSort(array2, 1), 1);
  ASSERT_EQ(array2[0], 1);

  ASSERT_EQ(ShellSort(array3, 10), 1);
  for (size_t i = 0; i < 10; ++i) {
    ASSERT_EQ(array3[i], i);
  }
}