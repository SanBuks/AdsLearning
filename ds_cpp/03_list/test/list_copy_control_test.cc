#include "list.h"

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

// 构造函数, 头插法, 尾插法, 寻秩访问 测试
TEST(CopyControlTest, TestDefaultCtor) {
  using namespace ds_cpp;

  List<int> list;
  EXPECT_EQ(list.Empty(), true);

  list.InsertAsFirst(1);
  list.InsertAsLast(2);
  EXPECT_EQ(list.size(), 2);

  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);

  const List<int> &const_list = list;
  EXPECT_EQ(const_list[0], 1);
  EXPECT_EQ(const_list[1], 2);

  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> list_array(array, 10);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(list_array[i], array[i]);
  }
}

// 拷贝构造函数 测试
TEST(CopyControlTest, TestCopyCtor) {
  using namespace ds_cpp;

  List<int> list;
  list.InsertAsFirst(1);
  list.InsertAsLast(2);

  List<int> list2(list);
  EXPECT_EQ(list2[0], 1);
  EXPECT_EQ(list2[1], 2);

  List<int> list3(std::move(list));
  EXPECT_EQ(list3.size(), 2);
  EXPECT_EQ(list.size(), 0);
}

// swap 测试
TEST(CopyControlTest, TestSwap) {
  using namespace ds_cpp;

  List<int> list1;
  list1.InsertAsFirst(1);
  list1.InsertAsLast(2);

  List<int> list2;
  list2.InsertAsFirst(10);
  list2.InsertAsLast(11);
  list2.InsertAsLast(12);

  swap(list1, list2);

  EXPECT_EQ(list1[0], 10);
  EXPECT_EQ(list1[1], 11);
  EXPECT_EQ(list1[2], 12);

  EXPECT_EQ(list2[0], 1);
  EXPECT_EQ(list2[1], 2);
}

// 重载赋值运算符 测试
TEST(CopyControlTest, TestOptAssign) {
  using namespace ds_cpp;

  List<int> list;

  List<int> list1;
  list1.InsertAsFirst(1);
  list1.InsertAsLast(2);

  list = list1;
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);


  List<int> list2;
  list2.InsertAsFirst(10);
  list2.InsertAsLast(11);
  list = std::move(list2);
  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[1], 11);
  EXPECT_EQ(list2.size(), 0);
}
