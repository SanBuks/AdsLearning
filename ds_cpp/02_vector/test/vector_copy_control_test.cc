#include "vector.h"

#include <cstdlib>
#include <exception>
#include <sstream>
#include <typeinfo>

#include <gtest/gtest.h>

// 拷贝控制测试 数据类
class CopyControlTest : public ::testing::Test {
 protected:
  void TearDown() override {
    delete [] array;
  }
  size_t low = 2, high = 4, array_size = 10;
  int *array = new int[array_size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
};

// 默认构造函数测试
TEST_F(CopyControlTest, TestDefaultCtor) {
  using namespace ds_cpp;

  // 默认构造函数 测试
  Vector<int> vec;
  ASSERT_TRUE(vec.Empty());
  ASSERT_EQ(vec.capacity(), VectorBase::kDefaultCapacity);
  ASSERT_THROW(Vector<int> overflow(-1), std::bad_alloc);

  // 值初始化构造函数 测试
  const VectorBase::Size kTestSize1 = VectorBase::kDefaultCapacity;
  Vector<int> vec1(kTestSize1);
  ASSERT_EQ(vec1.size(), kTestSize1);
  ASSERT_EQ(vec1.capacity(), kTestSize1 * 2);
  for (VectorBase::Rank i = 0; i != kTestSize1; ++i) {
    ASSERT_EQ(vec1[i], int());
  }
}

// 数组拷贝构造函数 测试
TEST_F(CopyControlTest, TestCopyArrayCtor) {
  using namespace ds_cpp;

  // 数组拷贝构造函数 测试 1 (2 * array_size >= VectorBase::kDefaultCapacity)
  Vector<int> vec1(array, array_size);
  ASSERT_EQ(vec1.size(), array_size);
  ASSERT_EQ(vec1.capacity(), vec1.size() * 2);
  for (VectorBase::Rank i = 0; i != array_size; ++i) {
    ASSERT_EQ(vec1[i], array[i]);
  }
  // 数组拷贝构造函数 测试 2 (2 * (high - low) >= VectorBase::kDefaultCapacity)
  ASSERT_LE(low, high);
  Vector<int> vec2(array, low, high);
  ASSERT_EQ(vec2.size(), high - low);
  ASSERT_EQ(vec2.capacity(), vec2.size() * 2);
  for (VectorBase::Rank i = 0; i != vec2.size(); ++i) {
    ASSERT_EQ(vec2[i], array[low + i]);
  }
  // 数组拷贝构造函数 测试 3
  ASSERT_THROW(Vector<int> vec3(array, 2, 1), std::runtime_error);
  ASSERT_THROW(Vector<int> vec4(array, 0, -1), std::bad_alloc);
}

// 拷贝构造函数 测试
TEST_F(CopyControlTest, TestCopyCtor) {
  using namespace ds_cpp;

  Vector<int> vec(array, array_size);

  // 拷贝构造函数 测试 1 (2 * array_size >= VectorBase::kDefaultCapacity)
  Vector<int> vec1(vec);
  ASSERT_EQ(vec1.size(), vec.size());
  ASSERT_EQ(vec1.capacity(), vec1.size() * 2);
  for (VectorBase::Rank i = 0; i != vec1.size(); ++i) {
    ASSERT_EQ(vec1[i], vec[i]);
  }
  // 拷贝构造函数 测试 2 (2 * (high - low) >= VectorBase::kDefaultCapacity)
  Vector<int> vec2(vec, low, high);
  ASSERT_EQ(vec2.size(), high - low);
  ASSERT_EQ(vec2.capacity(), vec2.size() * 2);
  for (VectorBase::Rank i = 0; i != vec2.size(); ++i) {
    ASSERT_EQ(vec2[i], vec[low + i]);
  }
  // 拷贝构造函数 测试 3
  ASSERT_THROW(Vector<int> vec3(vec, 1, 0), std::runtime_error);
  ASSERT_THROW(Vector<int> vec3(vec, 0, -1), std::runtime_error);
  ASSERT_THROW(Vector<int> vec3(vec, 0, array_size + 1), std::runtime_error);
  // 移动拷贝构造函数 测试 4
  Vector<int> vec4((Vector<int>(VectorBase::kDefaultCapacity)));
  ASSERT_EQ(vec4.size(), VectorBase::kDefaultCapacity);
  ASSERT_EQ(vec4.capacity(), VectorBase::kDefaultCapacity * 2);
  for (VectorBase::Rank i = 0; i != vec4.size(); ++i) {
    ASSERT_EQ(vec4[i], 0);
  }
}

// swap 测试
TEST_F(CopyControlTest, TestSwap) {
  using namespace ds_cpp;

  Vector<int> vec1(array, low, high);
  Vector<int> vec2(array, array_size);
  swap(vec1, vec2);
  for (VectorBase::Size i = 0; i != array_size; ++i) {
    ASSERT_EQ(vec1[i], array[i]);
  }
  for (VectorBase::Size i = 0; i != high - low; ++i) {
    ASSERT_EQ(vec2[i], array[low + i]);
  }
}

// 重载赋值运算符 测试
TEST_F(CopyControlTest, TestOptAssign) {
  using namespace ds_cpp;

  Vector<int> vec_assign(array, array_size);

  // 重载赋值运算符 测试
  Vector<int> vec1(5);
  ASSERT_EQ((vec1 = vec_assign).size(), vec_assign.size());
  for (VectorBase::Rank i = 0; i != array_size; ++i) {
    ASSERT_EQ(vec1[i], array[i]);
  }
  // 移动重载赋值运算符 测试
  Vector<int> vec2(5);
  vec2 = std::move(vec_assign);
  ASSERT_EQ(vec2.size(), array_size);
  ASSERT_TRUE(vec_assign.Empty());
  for (VectorBase::Rank i = 0; i != array_size; ++i) {
    ASSERT_EQ(vec2[i], array[i]);
  }
}