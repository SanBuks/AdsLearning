#include "list.h"

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

// 可写函数测试 数据类
class ModifyTest : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 1; i <= 10; ++i) {
      list1.InsertAsLast(i);
    }
  }

  void TearDown() override {
    delete [] array1;
    delete [] array2;
    delete [] duplicate_array;
    delete [] uniquify_array;
  }

  ds_cpp::List<int> list1;

  int array_size1 = 0;
  int array_size2 = 1;
  int array_size3 = 10;

  int *array1 = new int[array_size1]{};
  int *array2 = new int[array_size2]{1};
  int *duplicate_array = new int[array_size3]{2, 2, 3, 4, 1, 2, 7, 9, 11, 11};
  int *uniquify_array = new int[array_size3]{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
};

TEST_F(ModifyTest, TestInsert) {
  using namespace ds_cpp;

  auto p = list1.FindAfter(3, 3, list1.header());

  auto p1 = list1.InsertBefore(p, 100);
  EXPECT_EQ(list1.size(), 11);
  EXPECT_EQ(list1[2], 100);
  auto p11 = list1.InsertBefore(list1.header(), 100);
  EXPECT_EQ(p11, nullptr);

  list1.InsertAfter(p1, 101);
  EXPECT_EQ(list1.size(), 12);
  EXPECT_EQ(list1[3], 101);
  auto p22 = list1.InsertAfter(list1.header(), 100);
  EXPECT_EQ(p22, nullptr);
}

TEST_F(ModifyTest, TestRemove) {
  using namespace ds_cpp;

  auto p = list1.FindAfter(9, list1.size(), list1.header());

  EXPECT_EQ(list1.Remove(p), 9);
  EXPECT_EQ(list1[8], 10);
  EXPECT_EQ(list1[7], 8);

  EXPECT_THROW(list1.Remove(list1.header()), std::runtime_error);
  EXPECT_THROW(list1.Remove(nullptr), std::runtime_error);
}

TEST_F(ModifyTest, TestDeduplicate) {
  using namespace ds_cpp;

  List<int> list1(array1, array_size1);
  EXPECT_EQ(list1.Deduplicate(), 0);

  List<int> list2(array2, array_size2);
  EXPECT_EQ(list2.Deduplicate(), 0);

  List<int> list3(duplicate_array, 10);
  EXPECT_EQ(list3.Deduplicate(), 3);
  EXPECT_EQ(list3[6], 11);
}

TEST_F(ModifyTest, TestUniquify) {
  using namespace ds_cpp;

  List<int> list1(array1, array_size1);
  EXPECT_EQ(list1.Uniquify(), 0);

  List<int> list2(array2, array_size2);
  EXPECT_EQ(list2.Uniquify(), 0);

  List<int> list3(uniquify_array, 10);
  EXPECT_EQ(list3.Uniquify(), 6);
  EXPECT_EQ(list3[3], 4);
}
