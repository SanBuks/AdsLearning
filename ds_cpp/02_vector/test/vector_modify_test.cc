#include "vector.h"

#include <cstdlib>
#include <exception>
#include <sstream>

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

// 可写函数测试 数据类
class ModifyTest : public ::testing::Test {
 protected:
  void TearDown() override {
    delete [] array;
    delete [] array_dup;
    delete [] array_uni;
  }
  size_t low = 2, high = 4, array_size = 10;
  int *array = new int[array_size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int *array_dup = new int[array_size]{33, 1, 33, 7, 90, 0, 10, 7, 1, 2};
  int *array_uni = new int[array_size]{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
};

// 置乱
TEST_F(ModifyTest, TestUnsort) {
  using namespace ds_cpp;

  Vector<int> vec(array, array_size);
  EXPECT_EQ(vec.Disordered(), 0);
  VectorTraverse<int> traverse(std::cout);

  vec.Traverse(traverse);
  GTEST_COUT << "\n";

  vec.Unsort();
  EXPECT_GT(vec.Disordered(), 0);
  vec.Traverse(traverse);
  GTEST_COUT << "\n";

  vec.Unsort(0, 6);
  vec.Traverse(traverse);
  GTEST_COUT << "\n";
}

// 插入
TEST_F(ModifyTest, TestInsert) {
  using namespace ds_cpp;

  Vector<int> vec(array, array_size);
  for (int i = 0; i < 11; ++i) {
    vec.Insert(99);
  }
  EXPECT_EQ(vec[vec.size() - 1], 99);
  EXPECT_EQ(vec.capacity(), 40);

  vec.Insert(2, 333);
  EXPECT_EQ(vec[2], 333);
}

// 删除
TEST_F(ModifyTest, TestRemove) {
  using namespace ds_cpp;

  Vector<int> vec(array, array_size);
  vec.Remove(0, 3);
  EXPECT_EQ(vec[0], 4);

  vec.Remove(0, 4);
  EXPECT_EQ(vec.capacity(), 10);
  vec.Remove(0);
  EXPECT_EQ(vec[0], 9);
}

// 无序去重
TEST_F(ModifyTest, TestDeduplicate) {
  using namespace ds_cpp;

  Vector<int> vec1(array_dup, array_size);
  vec1.Deduplicate();
  EXPECT_EQ(vec1.size(), 7);

  Vector<int> vec2(array_dup, array_size);
  vec2.Deduplicate(0, 3);
  EXPECT_EQ(vec2.size(), 9);
}

// 有序去重
TEST_F(ModifyTest, TestUniquify) {
  using namespace ds_cpp;

  Vector<int> vec1(array_uni, array_size);
  vec1.Uniquify();
  EXPECT_EQ(vec1.size(), 4);

  Vector<int> vec2(array_uni, array_size);
  vec2.Deduplicate(0, 5);
  EXPECT_EQ(vec2.size(), 8);
}

// 转置 测试
TEST_F(ModifyTest, TestReverse) {
  using namespace ds_cpp;

  Vector<int> vec(array, array_size);
  std::stringstream ss;
  VectorTraverse<int> traverse(ss);

  vec.Reverse();
  vec.Traverse(traverse);

  auto &os = dynamic_cast<std::stringstream &>(traverse.io());
  EXPECT_EQ(os.str(), "10 9 8 7 6 5 4 3 2 1 ");
  ss.str("");

  vec.Reverse(0, 5);
  vec.Traverse(traverse);
  EXPECT_EQ(os.str(), "6 7 8 9 10 5 4 3 2 1 ");
}
