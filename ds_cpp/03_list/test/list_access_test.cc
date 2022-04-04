#include "list.h"

#include <sstream>
#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

// 只读函数测试 数据类
class AccessTest : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 1; i <= 10; ++i) {
      list1.InsertAsLast(i);
    }
  }

  ds_cpp::List<int> list1;

  int array_size1 = 0;
  int array_size2 = 1;
  int array_size3 = 10;

  int *array1 = new int[array_size1]{};
  int *array2 = new int[array_size2]{1};
  int *array3 = new int[array_size3]{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
};

// 遍历测试
TEST_F(AccessTest, TestTraverse) {
  using namespace ds_cpp;

  const List<int> &const_list1 = list1;

  std::ostringstream oss;
  ListTraverse<int> traverse(oss);

  auto &str_stream = dynamic_cast<std::ostringstream &>(traverse.io());

  list1.Traverse(traverse);
  ASSERT_EQ(str_stream.str(), "1 2 3 4 5 6 7 8 9 10 ");
  str_stream.str("");

  const_list1.Traverse(traverse);
  ASSERT_EQ(str_stream.str(), "1 2 3 4 5 6 7 8 9 10 ");
  str_stream.str("");
}

// 无序查找, 向前查找
TEST_F(AccessTest, TestFindBefore) {
  using namespace ds_cpp;

  auto p1 = list1.FindBefore(8, 3, list1.trailer());
  EXPECT_EQ(p1->data(), 8);

  auto p2 = list1.FindBefore(2, 5, p1);
  EXPECT_EQ(p2, nullptr);

  auto p3 = list1.FindBefore(0, 8, p1);
  EXPECT_EQ(p3, nullptr);

  auto p4 = list1.FindBefore(0, 100, p1);
  EXPECT_EQ(p4, nullptr);

  auto p5 = list1.FindBefore(0, 0, nullptr);
  EXPECT_EQ(p5, nullptr);

  auto p6 = list1.FindBefore(0, 1, nullptr);
  EXPECT_EQ(p6, nullptr);
}

// 无序查找, 向后查找
TEST_F(AccessTest, TestFindAfter) {
  using namespace ds_cpp;

  auto p1 = list1.FindAfter(3, 3, list1.header());
  EXPECT_EQ(p1->data(), 3);

  auto p2 = list1.FindAfter(9, 5, p1);
  EXPECT_EQ(p2, nullptr);

  auto p3 = list1.FindAfter(0, 8, p1);
  EXPECT_EQ(p3, nullptr);

  auto p4 = list1.FindAfter(0, 100, p1);
  EXPECT_EQ(p4, nullptr);

  auto p5 = list1.FindAfter(0, 0, nullptr);
  EXPECT_EQ(p5, nullptr);

  auto p6 = list1.FindAfter(0, 1, nullptr);
  EXPECT_EQ(p6, nullptr);
}

// 有序查找, 向前查找
TEST_F(AccessTest, TestSearchBefore) {
  using namespace ds_cpp;

  auto p1 = list1.SearchBefore(8, 3, list1.trailer());
  EXPECT_EQ(p1->data(), 8);

  auto p2 = list1.SearchBefore(2, 5, p1);
  EXPECT_EQ(2, p2->data());

  auto p3 = list1.SearchBefore(0, 8, p1);
  EXPECT_EQ(p3, list1.header());

  auto p4 = list1.SearchBefore(0, 100, p1);
  EXPECT_EQ(p4, list1.header());

  EXPECT_THROW(auto p5 = list1.SearchBefore(0, 0, nullptr),
               std::runtime_error);

  auto p6 = list1.SearchBefore(0, 0, p1);
  EXPECT_EQ(p6->data(), 7);
}

// 有序查找, 向后查找
TEST_F(AccessTest, TestSearchAfter) {
  using namespace ds_cpp;

  auto p1 = list1.SearchAfter(3, 3, list1.header());
  EXPECT_EQ(p1->data(), 2);

  auto p2 = list1.SearchAfter(9, 5, p1);
  EXPECT_EQ(p2->data(), 7);

  auto p3 = list1.SearchAfter(11, 9, p1);
  EXPECT_EQ(p3->data(), 10);

  auto p4 = list1.SearchAfter(11, 100, p1);
  EXPECT_EQ(p4->data(), 10);

  EXPECT_THROW(auto p5 = list1.SearchAfter(0, 0, nullptr),
               std::runtime_error);

  auto p6 = list1.SearchAfter(11, 0, p1);
  EXPECT_EQ(p6->data(), 2);
}

TEST_F(AccessTest, TestDisordered) {
  using namespace ds_cpp;

  List<int> list1(array1, array_size1);
  List<int> list2(array2, array_size2);
  List<int> list3(array3, array_size3);

  EXPECT_EQ(list1.Disordered(), 0);
  EXPECT_EQ(list2.Disordered(), 0);
  EXPECT_EQ(list3.Disordered(), 9);
}

TEST_F(AccessTest, TestMax) {
  using namespace ds_cpp;

  List<int> list1(array1, array_size1);
  List<int> list2(array2, array_size2);
  List<int> list3(array3, array_size3);

  auto pf1 = list1.header()->succ();
  auto pf2 = list2.header()->succ();
  auto pf3 = list3.header()->succ();

  auto p1 = list1.Max(pf1, 3);
  auto p2 = list2.Max(pf2, 10);
  auto p3 = list3.Max(pf3, 11);
  EXPECT_EQ(p1, nullptr);
  EXPECT_EQ(pf2->data(), 1);
  EXPECT_EQ(pf3->data(), 10);
}
