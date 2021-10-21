#include "../include/dsa_cpp/vector/vector.h"

#include <cstdlib>
#include <exception>
#include <queue>
#include <sstream>
#include <typeinfo>

#include <gtest/gtest.h>

// 测试构造函数
class TestCtor : public ::testing::Test {
 protected:
  TestCtor() = default;
  void TearDown() override {
    delete [] array;
  }

  size_t array_size = 10;
  int *array = new int[array_size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  size_t low_pos = 2;
  size_t high_pos = 4;
};
// 默认构造函数 测试
TEST_F(TestCtor, TestDefaultConstructor) {
  using namespace dsa_cpp;

  // 默认构造函数
  Vector<int> vec_default;
  ASSERT_TRUE(vec_default.Empty());
  ASSERT_EQ(vec_default.capacity(), VectorBase::kDefaultCapacity);
  ASSERT_THROW({Vector<int> overflow(-1);}, std::runtime_error);
  // 默认构造函数值初始化
  constexpr const VectorBase::Size kDefaultSize = 3;
  Vector<int> vec_value_initial(kDefaultSize);
  ASSERT_EQ(vec_value_initial.size(), kDefaultSize);
  ASSERT_EQ(vec_value_initial.capacity(), vec_value_initial.size() * 2);
  for (VectorBase::Rank i = 0; i != vec_value_initial.size(); ++i) {
    ASSERT_EQ(vec_value_initial[i], int());
  }
}
// 拷贝构造函数 测试
TEST_F(TestCtor, TestCopyConstructor) {
  using namespace dsa_cpp;

  // 拷贝构造函数 (数组1)
  Vector<int> vec_copy_from_array1(array, array_size);
  ASSERT_EQ(vec_copy_from_array1.size(), array_size);
  ASSERT_EQ(vec_copy_from_array1.capacity(), vec_copy_from_array1.size() * 2);
  for (VectorBase::Rank i = 0; i != array_size; ++i) {
    ASSERT_EQ(vec_copy_from_array1[i], array[i]);
  }
  // 拷贝构造函数 (数组2)
  ASSERT_LE(low_pos, high_pos);
  Vector<int> vec_copy_from_array2(array, low_pos, high_pos);
  ASSERT_EQ(vec_copy_from_array2.size(), high_pos - low_pos);
  ASSERT_EQ(vec_copy_from_array2.capacity(), vec_copy_from_array2.size() * 2);
  for (VectorBase::Rank i = 0;
       i != vec_copy_from_array2.size();
       ++i) {
    ASSERT_EQ(vec_copy_from_array2[i], array[low_pos + i]);
  }

  ASSERT_ANY_THROW({
     Vector<int> vec_copy_from_array3(array, low_pos + 100, high_pos);
  });

  Vector<int> vec(array, array_size);
  // 拷贝构造函数 (Vector1)
  Vector<int> vec_copy_from_vector1(vec);
  ASSERT_EQ(vec_copy_from_vector1.size(), vec.size());
  ASSERT_EQ(vec_copy_from_vector1.capacity(),
            vec_copy_from_vector1.size() * 2);
  for (VectorBase::Rank i = 0;
       i != vec_copy_from_vector1.size();
       ++i) {
    ASSERT_EQ(vec_copy_from_vector1[i], vec[i]);
  }
  // 拷贝构造函数 (Vector2)
  ASSERT_LE(low_pos, high_pos);
  Vector<int> vec_copy_from_vector2(vec, low_pos, high_pos);
  ASSERT_EQ(vec_copy_from_vector2.size(), high_pos - low_pos);
  ASSERT_EQ(vec_copy_from_vector2.capacity(),
            vec_copy_from_vector2.size() * 2);
  for (VectorBase::Rank i = 0;
       i != vec_copy_from_vector2.size();
       ++i) {
    ASSERT_EQ(vec_copy_from_vector2[i], vec[low_pos + i]);
  }

  ASSERT_ANY_THROW({
     Vector<int> vec_copy_from_vector3(vec, low_pos + 100, high_pos);
  });
}

// 测试只读函数
class OnlyReadTest: public ::testing::Test {
 protected:
  OnlyReadTest() : array_size(10),
                   array(new int[array_size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}),
                   vec(array, array_size), vec_const(array, array_size) { }
  void TearDown() override {
    delete [] array;
  }

  size_t array_size;
  int *array;
  dsa_cpp::Vector<int> vec;
  const dsa_cpp::Vector<int> vec_const;
};
// 重载赋值运算符 测试
TEST_F(OnlyReadTest, TestOperatorEqual) {
  using namespace dsa_cpp;

  Vector<int> vec_operator_equal;
  vec_operator_equal = vec;
  ASSERT_EQ(vec_operator_equal.size(), vec.size());
  ASSERT_EQ(vec_operator_equal.capacity(), vec_operator_equal.size() * 2);
  for (VectorBase::Rank i = 0; i != vec_operator_equal.size(); ++i) {
    ASSERT_EQ( vec_operator_equal[i], vec[i]);
  }
}
// 遍历 测试
TEST_F(OnlyReadTest, TestTraverse) {
  using namespace dsa_cpp;

  std::ostringstream oss;
  dsa_cpp::VectorTraverse<int> traverse(oss);
  vec.Traverse(traverse);
  try {
    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
    ASSERT_EQ(str_stream.str(), std::string("1 2 3 4 5 6 7 8 9 10 "));
    str_stream.str("");
    vec_const.Traverse(traverse);
    ASSERT_EQ(str_stream.str(), std::string("1 2 3 4 5 6 7 8 9 10 "));
  } catch (std::bad_cast &ex) {
    FAIL() << ex.what();
  }
}
// 统计相邻逆序数 测试
TEST_F(OnlyReadTest, TestDisordered) {
  using namespace dsa_cpp;

  Vector<int> empty;
  Vector<int> only_one;
  const int kSize = 10;
  int a[kSize] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  Vector<int> vec(a, kSize);
  ASSERT_EQ(vec.Disordered(), kSize - 1);
}
// 无序查找 测试
TEST_F(OnlyReadTest, TestFind) {
  using namespace dsa_cpp;

  ASSERT_EQ(4, vec.Find(5));
  ASSERT_EQ(4, vec.Find(5, 0, 5));
  ASSERT_EQ(VectorBase::kNonPosition, vec.Find(5, 0, 3));
  ASSERT_EQ(VectorBase::kNonPosition, vec.Find(100));
}
// 区间查找自大值 测试
TEST_F(OnlyReadTest, TestMax) {
  using namespace dsa_cpp;

  ASSERT_EQ(vec.Max(), vec.size() - 1);
}

// 测试增删改函数
class OnlyModifyTest : public ::testing::Test {
 protected:
  OnlyModifyTest () : array_size(5),
                      array(new int[array_size]{1, 2, 3, 4, 5}),
                      vec(array, array_size) {}
  void TearDown() override {
    delete [] array;
  }

  size_t array_size;
  int *array;
  dsa_cpp::Vector<int> vec;
};
// 插入 测试
TEST_F(OnlyModifyTest, TestInsert) {
  using namespace std;

  std::ostringstream oss;
  dsa_cpp::VectorTraverse<int> traverse(oss);

  auto old_size = vec.size();
  vec.Insert(0, 0);
  vec.Traverse(traverse);
  try {
    ASSERT_EQ(vec.size(), old_size + 1);
    ASSERT_EQ(vec.capacity(), 10);
    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
    ASSERT_EQ(str_stream.str(), std::string("0 1 2 3 4 5 "));
    str_stream.str("");
  } catch (std::bad_cast &ex) {
    FAIL() << ex.what();
  }

  auto old_capacity = vec.capacity();
  old_size = vec.size();
  for (size_t i = 0 ; i < 5; ++i) {
    vec.Insert(0);
  }
  ASSERT_EQ(vec.capacity(), 2 * old_capacity);
  ASSERT_EQ(vec.size(), old_size + 5);
}
// 删除 测试
TEST_F(OnlyModifyTest, TestRemove) {
  using namespace std;

  std::ostringstream oss;
  dsa_cpp::VectorTraverse<int> traverse(oss);

  auto old_size = vec.size();
  auto old_capacity = vec.capacity();
  auto remove_size = vec.Remove(2, vec.size());
  vec.Traverse(traverse);
  try {
    ASSERT_EQ(vec.size(), old_size - remove_size);
    ASSERT_EQ(vec.capacity(), old_capacity >> 1);
    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
    ASSERT_EQ(str_stream.str(), std::string("1 2 "));
    str_stream.str("");
  } catch (std::bad_cast &ex) {
    FAIL() << ex.what();
  }

  ASSERT_EQ(1, vec.Remove(0));
  ASSERT_EQ(2, vec.Remove(0));
  ASSERT_EQ(vec.Empty(), true);
}
// 转置 测试
TEST_F(OnlyModifyTest, TestReverse) {
  using namespace std;

  std::ostringstream oss;
  dsa_cpp::VectorTraverse<int> traverse(oss);
  try {
    vec.Reverse(0, 0);
    vec.Traverse(traverse);
    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
    ASSERT_EQ(str_stream.str(), std::string("1 2 3 4 5 "));
    str_stream.str("");

    vec.Reverse(0, 1);
    vec.Traverse(traverse);
    ASSERT_EQ(str_stream.str(), std::string("1 2 3 4 5 "));
    str_stream.str("");

    vec.Reverse(0, vec.size());
    vec.Traverse(traverse);
    ASSERT_EQ(str_stream.str(), std::string("5 4 3 2 1 "));
    str_stream.str("");
  } catch (std::bad_cast &ex) {
    FAIL();
  }
}
// 无序去重 测试
TEST_F(OnlyModifyTest, TestDeduplicate) {
  using namespace dsa_cpp;

  std::ostringstream oss;
  dsa_cpp::VectorTraverse<int> traverse(oss);
  vec.Insert(1);
  vec.Insert(2);
  vec.Insert(3);
  vec.Insert(4);
  vec.Insert(5);
  auto deduction = vec.Deduplicate();
  try {
    vec.Traverse(traverse);
    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
    ASSERT_EQ(str_stream.str(), "1 2 3 4 5 ");
    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(deduction, 5);
    deduction = vec.Deduplicate(0, 3);
    ASSERT_EQ(deduction, 0);
  } catch (std::bad_cast &ex) {
    FAIL();
  }
}
// 有序去重 测试
TEST_F(OnlyModifyTest, TestUniquify) {
  using namespace dsa_cpp;

  std::ostringstream oss;
  dsa_cpp::VectorTraverse<int> traverse(oss);
  vec.Insert(5);
  vec.Insert(6);
  vec.Insert(6);
  vec.Insert(7);
  vec.Insert(8);
  auto deduction = vec.Uniquify();
  try {
    vec.Traverse(traverse);
    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
    ASSERT_EQ(str_stream.str(), "1 2 3 4 5 6 7 8 ");
    ASSERT_EQ(vec.size(), 8);
    ASSERT_EQ(deduction, 2);
    deduction = vec.Deduplicate(0, 3);
    ASSERT_EQ(deduction, 0);
  } catch (std::bad_cast &ex) {
    FAIL();
  }
}
// 置乱 测试
TEST_F(OnlyModifyTest, TestUnsort) {
  using namespace dsa_cpp;

  std::ostringstream oss;
  dsa_cpp::VectorTraverse<int> traverse(oss);
  auto old_size = vec.size();
  int last_elem = vec[old_size - 1];
  vec.Unsort(0, old_size - 1);
  try {
    vec.Traverse(traverse);
    auto &str_stream = dynamic_cast<std::ostringstream&>(traverse.io());
    std::cout << "unsorted vec is : " << str_stream.str() << "\n";
    ASSERT_EQ(vec.size(), old_size);
    ASSERT_EQ(last_elem, vec[old_size - 1]);
  } catch (std::bad_cast &ex) {
    FAIL();
  }
}

/*
void TestBinSearch() {
  int a[] = {1, 2, 2, 2, 3, 3, 4, 4, 4, 7, 9};
  my_ads::Vector<int> vec(a, sizeof(a) / sizeof(int));
  vec.Traverse<VisitInt>(vst);
  std::cout << "\n" << vec.BinSearch(2, 0, vec.size()) << "\n";
  vec.Traverse<VisitInt>(vst);
}

void TestBubbleSort() {
  int a[] = {1, 2, 2, 2, 3, 3, 4, 4, 4, 7, 9};
  my_ads::Vector<int> vec(a, sizeof(a) / sizeof(int));
  vec.Unsort();
  vec.Traverse<VisitInt>(vst);

  std::cout << "\n";
  vec.BubbleSort();
  vec.Traverse<VisitInt>(vst);
}

void TestMergeSort() {
  int a[] = {1, 2, 3};
  my_ads::Vector<int> vec(a, sizeof(a) / sizeof(int));
  vec.Unsort();
  vec.Traverse<VisitInt>(vst);

  std::cout << "\n";
  vec.MergeSort(0, vec.size());
  vec.Traverse<VisitInt>(vst);
}

unsigned long CalcCompareTimes(unsigned long k) {
  if (k == 1) { 
    return 1;
  }

  unsigned long result = 2 * CalcCompareTimes(k - 1);
  result += (3 * (1 << (k-1)) -1);  

  return result;
}
*/