#include "vector.h"

#include <cstdlib>
#include <sstream>
#include <exception>

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

// 只读函数测试 数据类
class AccessTest : public ::testing::Test {
 protected:
  void TearDown() override {
    delete [] array;
    delete [] array_search;
    delete [] array_disordered;
  }
  size_t low = 2, high = 4, array_size = 10;
  int *array = new int[array_size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int *array_search = new int[array_size]{1, 1, 2, 2, 3, 5, 5, 5, 9, 10};
  int *array_disordered = new int[array_size]{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
};

// 遍历测试
TEST_F(AccessTest, TestTraverse) {
  using namespace ds_cpp;

  std::ostringstream oss;
  VectorTraverse<int> traverse(oss);

  Vector<int> vec(array, array_size);
  const Vector<int> const_vec(array, array_size);
  auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());

  vec.Traverse(traverse);
  ASSERT_EQ(str_stream.str(), "1 2 3 4 5 6 7 8 9 10 ");
  str_stream.str("");

  const_vec.Traverse(traverse);
  ASSERT_EQ(str_stream.str(), "1 2 3 4 5 6 7 8 9 10 ");
  str_stream.str("");
}

// 无序查找
TEST_F(AccessTest, TestFind) {
  using namespace ds_cpp;

  Vector<int> vec(array, array_size);
  EXPECT_EQ(6, vec.Find(7));
  EXPECT_EQ(VectorBase::kNonPosition, vec.Find(100));
  EXPECT_EQ(VectorBase::kNonPosition, vec.Find(7, 0, 3));
  EXPECT_EQ(3, vec.Find(4, 0, 7));
}

// 二分查找
TEST_F(AccessTest, TestBinSearch) {
  using namespace ds_cpp;

  Vector<int> vec(array_search, array_size);
  EXPECT_EQ(vec.BinSearch(3), 4);
  EXPECT_EQ(vec.BinSearch(100, 0, 3), 2);
  EXPECT_EQ(vec.BinSearch(1, 0, 3), 1);
  EXPECT_EQ(vec.BinSearch(-1, 0, 3), VectorBase::kNonPosition);
}

// Fib查找
TEST_F(AccessTest, TestFibSearch) {
  using namespace ds_cpp;

  Vector<int> vec(array_search, array_size);
  EXPECT_EQ(vec.FibSearch(3), 4);
  EXPECT_EQ(vec.FibSearch(100, 0, 3), 2);
  EXPECT_EQ(vec.FibSearch(1, 0, 3), 1);
  EXPECT_EQ(vec.FibSearch(-1, 0, 3), VectorBase::kNonPosition);
}

// 区间 最大值查找
TEST_F(AccessTest, TestMax) {
  using namespace ds_cpp;

  Vector<int> vec(array, array_size);
  EXPECT_EQ(vec[vec.Max()], 10);
  EXPECT_EQ(vec[vec.Max(0, 3)], 3);
  EXPECT_EQ(vec.Max(0, 0), VectorBase::kNonPosition);
}

// 统计相邻逆序数 测试
TEST_F(AccessTest, TestDisordered) {
  using namespace ds_cpp;

  Vector<int> vec(array, array_size);
  Vector<int> vec_disordered(array_disordered, array_size);
  ASSERT_EQ(vec.Disordered(), 0);
  ASSERT_EQ(vec_disordered.Disordered(), 9);
}
