#include "list.h"

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

// 排序函数测试 数据类
class SortTest : public ::testing::Test {
 protected:
  void TearDown() override {
    delete [] array1;
    delete [] array2;
    delete [] array3;
  }

  ds_cpp::List<int> list1;

  int array_size1 = 0;
  int array_size2 = 1;
  int array_size3 = 10;

  int *array1 = new int[array_size1]{};
  int *array2 = new int[array_size2]{1};
  int *array3 = new int[array_size3]{7, 1, 3, 2, 10, 9, 6, 5, 33, 111};
};

TEST_F(SortTest, TestInsertSort) {
  using namespace ds_cpp;

  List<int> list1(array1, array_size1);
  List<int> list2(array2, array_size2);
  List<int> list3(array3, array_size3);

  list1.InsertSort();
  list2.InsertSort();
  list3.InsertSort();

  EXPECT_EQ(list1.Disordered(), 0);
  EXPECT_EQ(list1.size(), 0);

  EXPECT_EQ(list2.Disordered(), 0);
  EXPECT_EQ(list2.size(), 1);

  EXPECT_EQ(list3.Disordered(), 0);
  EXPECT_EQ(list3.size(), 10);
}