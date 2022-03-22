#include "vector.h"

#include <cstdlib>
#include <exception>

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
  size_t low = 2, high = 4, array_size = 10;
  int *array1 = new int[0]{};
  int *array2 = new int[1]{1};
  int *array3 = new int[array_size]{7, 3, 9, 4, 5, 0, 1, 8, 2, 6};
};

// 冒泡排序测试
TEST_F(SortTest, TestBubbleSort) {
  using namespace ds_cpp;

  Vector<int> vec1(array1, 0);
  vec1.BubbleSort();

  Vector<int> vec2(array2, 1);
  vec2.BubbleSort();
  EXPECT_EQ(vec2[0], 1);

  Vector<int> vec3(array3, array_size);
  vec3.BubbleSort();
  for (int i = 0; i < array_size; ++i) {
    EXPECT_EQ(vec3[i], i);
  }

  Vector<int> vec4(array3, array_size);
  vec4.BubbleSort(5, 10);
  EXPECT_EQ(vec4[5], 0);
  EXPECT_EQ(vec4[6], 1);
  EXPECT_EQ(vec4[7], 2);
  EXPECT_EQ(vec4[8], 6);
  EXPECT_EQ(vec4[9], 8);
}

// 选择排序测试
TEST_F(SortTest, TestSelectSort) {
  using namespace ds_cpp;

  Vector<int> vec1(array1, 0);
  vec1.SelectSort();

  Vector<int> vec2(array2, 1);
  vec2.SelectSort();
  EXPECT_EQ(vec2[0], 1);

  Vector<int> vec3(array3, array_size);
  vec3.SelectSort();
  for (int i = 0; i < array_size; ++i) {
    EXPECT_EQ(vec3[i], i);
  }

  Vector<int> vec4(array3, array_size);
  vec4.SelectSort(5, 10);
  EXPECT_EQ(vec4[5], 0);
  EXPECT_EQ(vec4[6], 1);
  EXPECT_EQ(vec4[7], 2);
  EXPECT_EQ(vec4[8], 6);
  EXPECT_EQ(vec4[9], 8);
}

// 插入排序测试
TEST_F(SortTest, TestInsertSort) {
  using namespace ds_cpp;

  Vector<int> vec1(array1, 0);
  vec1.InsertSort();

  Vector<int> vec2(array2, 1);
  vec2.InsertSort();
  EXPECT_EQ(vec2[0], 1);

  Vector<int> vec3(array3, array_size);
  vec3.InsertSort();

  for (int i = 0; i < array_size; ++i) {
    EXPECT_EQ(vec3[i], i);
  }

  Vector<int> vec4(array3, array_size);
  vec4.InsertSort(5, 10);
  EXPECT_EQ(vec4[5], 0);
  EXPECT_EQ(vec4[6], 1);
  EXPECT_EQ(vec4[7], 2);
  EXPECT_EQ(vec4[8], 6);
  EXPECT_EQ(vec4[9], 8);
}

// 归并排序测试
TEST_F(SortTest, TestMergeSort) {
  using namespace ds_cpp;

  Vector<int> vec1(array1, 0);
  vec1.MergeSort();

  Vector<int> vec2(array2, 1);
  vec2.MergeSort();
  EXPECT_EQ(vec2[0], 1);

  Vector<int> vec3(array3, array_size);
  vec3.MergeSort();

  for (int i = 0; i < array_size; ++i) {
    EXPECT_EQ(vec3[i], i);
  }

  Vector<int> vec4(array3, array_size);
  vec4.MergeSort(5, 10);
  EXPECT_EQ(vec4[5], 0);
  EXPECT_EQ(vec4[6], 1);
  EXPECT_EQ(vec4[7], 2);
  EXPECT_EQ(vec4[8], 6);
  EXPECT_EQ(vec4[9], 8);
}
