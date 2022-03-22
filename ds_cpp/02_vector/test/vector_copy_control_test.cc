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
  ASSERT_THROW(Vector<int> overflow(-1), std::runtime_error);

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
  ASSERT_THROW(Vector<int> vec4(array, 0, -1), std::runtime_error);
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


//// 统计相邻逆序数 测试
//TEST_F(OnlyReadTest, TestDisordered) {
//  using namespace ds_cpp;
//
//  Vector<int> empty;
//  Vector<int> only_one;
//  const int kSize = 10;
//  int a[kSize] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
//  Vector<int> vec(a, kSize);
//  ASSERT_EQ(vec.Disordered(), kSize - 1);
//}
//// 区间查找自大值 测试
//TEST_F(OnlyReadTest, TestMax) {
//  using namespace ds_cpp;
//
//  ASSERT_EQ(vec.Max(), vec.size() - 1);
//}
//
//// 测试增删改函数
//class OnlyModifyTest : public ::testing::Test {
// protected:
//  OnlyModifyTest () : array_size(5),
//                      array(new int[array_size]{1, 2, 3, 4, 5}),
//                      vec(array, array_size) {}
//  void TearDown() override {
//    delete [] array;
//  }
//
//  size_t array_size;
//  int *array;
//  ds_cpp::Vector<int> vec;
//};
//// 插入 测试
//TEST_F(OnlyModifyTest, TestInsert) {
//  using namespace std;
//
//  std::ostringstream oss;
//  ds_cpp::VectorTraverse<int> traverse(oss);
//
//  auto old_size = vec.size();
//  vec.Insert(0, 0);
//  vec.Traverse(traverse);
//  try {
//    ASSERT_EQ(vec.size(), old_size + 1);
//    ASSERT_EQ(vec.capacity(), 10);
//    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
//    ASSERT_EQ(str_stream.str(), std::string("0 1 2 3 4 5 "));
//    str_stream.str("");
//  } catch (std::bad_cast &ex) {
//    FAIL() << ex.what();
//  }
//
//  auto old_capacity = vec.capacity();
//  old_size = vec.size();
//  for (size_t i = 0 ; i < 5; ++i) {
//    vec.Insert(0);
//  }
//  ASSERT_EQ(vec.capacity(), 2 * old_capacity);
//  ASSERT_EQ(vec.size(), old_size + 5);
//}
//// 删除 测试
//TEST_F(OnlyModifyTest, TestRemove) {
//  using namespace std;
//
//  std::ostringstream oss;
//  ds_cpp::VectorTraverse<int> traverse(oss);
//
//  auto old_size = vec.size();
//  auto old_capacity = vec.capacity();
//  auto remove_size = vec.Remove(2, vec.size());
//  vec.Traverse(traverse);
//  try {
//    ASSERT_EQ(vec.size(), old_size - remove_size);
//    ASSERT_EQ(vec.capacity(), old_capacity >> 1);
//    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
//    ASSERT_EQ(str_stream.str(), std::string("1 2 "));
//    str_stream.str("");
//  } catch (std::bad_cast &ex) {
//    FAIL() << ex.what();
//  }
//
//  ASSERT_EQ(1, vec.Remove(0));
//  ASSERT_EQ(2, vec.Remove(0));
//  ASSERT_EQ(vec.Empty(), true);
//}
//// 转置 测试
//TEST_F(OnlyModifyTest, TestReverse) {
//  using namespace std;
//
//  std::ostringstream oss;
//  ds_cpp::VectorTraverse<int> traverse(oss);
//  try {
//    vec.Reverse(0, 0);
//    vec.Traverse(traverse);
//    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
//    ASSERT_EQ(str_stream.str(), std::string("1 2 3 4 5 "));
//    str_stream.str("");
//
//    vec.Reverse(0, 1);
//    vec.Traverse(traverse);
//    ASSERT_EQ(str_stream.str(), std::string("1 2 3 4 5 "));
//    str_stream.str("");
//
//    vec.Reverse(0, vec.size());
//    vec.Traverse(traverse);
//    ASSERT_EQ(str_stream.str(), std::string("5 4 3 2 1 "));
//    str_stream.str("");
//  } catch (std::bad_cast &ex) {
//    FAIL();
//  }
//}
//// 无序去重 测试
//TEST_F(OnlyModifyTest, TestDeduplicate) {
//  using namespace ds_cpp;
//
//  std::ostringstream oss;
//  ds_cpp::VectorTraverse<int> traverse(oss);
//  vec.Insert(1);
//  vec.Insert(2);
//  vec.Insert(3);
//  vec.Insert(4);
//  vec.Insert(5);
//  auto deduction = vec.Deduplicate();
//  try {
//    vec.Traverse(traverse);
//    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
//    ASSERT_EQ(str_stream.str(), "1 2 3 4 5 ");
//    ASSERT_EQ(vec.size(), 5);
//    ASSERT_EQ(deduction, 5);
//    deduction = vec.Deduplicate(0, 3);
//    ASSERT_EQ(deduction, 0);
//  } catch (std::bad_cast &ex) {
//    FAIL();
//  }
//}
//// 有序去重 测试
//TEST_F(OnlyModifyTest, TestUniquify) {
//  using namespace ds_cpp;
//
//  std::ostringstream oss;
//  ds_cpp::VectorTraverse<int> traverse(oss);
//  vec.Insert(5);
//  vec.Insert(6);
//  vec.Insert(6);
//  vec.Insert(7);
//  vec.Insert(8);
//  auto deduction = vec.Uniquify();
//  try {
//    vec.Traverse(traverse);
//    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
//    ASSERT_EQ(str_stream.str(), "1 2 3 4 5 6 7 8 ");
//    ASSERT_EQ(vec.size(), 8);
//    ASSERT_EQ(deduction, 2);
//    deduction = vec.Deduplicate(0, 3);
//    ASSERT_EQ(deduction, 0);
//  } catch (std::bad_cast &ex) {
//    FAIL();
//  }
//}
//// 置乱 测试
//TEST_F(OnlyModifyTest, TestUnsort) {
//  using namespace ds_cpp;
//
//  std::ostringstream oss;
//  ds_cpp::VectorTraverse<int> traverse(oss);
//  auto old_size = vec.size();
//  int last_elem = vec[old_size - 1];
//  vec.Unsort(0, old_size - 1);
//  try {
//    vec.Traverse(traverse);
//    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
//    std::cout << "unsorted vec is : " << str_stream.str() << "\n";
//    ASSERT_EQ(vec.size(), old_size);
//    ASSERT_EQ(last_elem, vec[old_size - 1]);
//  } catch (std::bad_cast &ex) {
//    FAIL();
//  }
//}


//unsigned long CalcCompareTimes(unsigned long k) {
//  if (k == 1) {
//    return 1;
//  }
//
//  unsigned long result = 2 * CalcCompareTimes(k - 1);
//  result += (3 * (1 << (k-1)) -1);
//
//  return result;
//}