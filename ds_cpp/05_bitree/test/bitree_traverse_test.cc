#include "bitree.h"
#include "vector.h"

#include <iostream>
#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

class TraverseTest : public ::testing::Test {
 protected:
  TraverseTest() : vec1(array1, array_size1),
                   vec2(array2, array_size2),
                   vec3(array3, array_size3),
                   vec4(array4, array_size4) {}

  void TearDown() override {
    delete [] array1;
    delete [] array2;
    delete [] array3;
    delete [] array4;
  }

  int array_size1 = 0;
  int array_size2 = 1;
  int array_size3 = 15;
  int array_size4 = 11;


  int *array1 = new int[array_size1]{};
  int *array2 = new int[array_size2]{0};
  int *array3 = new int[array_size3]{1, 2, 3, 4, 5, 0, 6, 0, 0, 7, 0, 0, 0, 0, 0};
  int *array4 = new int[array_size4]{1, 2, 3, 0, 4, 5, 0, 0, 0, 0, 0};

  ds_cpp::Vector<int> vec1;
  ds_cpp::Vector<int> vec2;
  ds_cpp::Vector<int> vec3;
  ds_cpp::Vector<int> vec4;
  // array3:
  //        1
  //    2       3
  // 4     5       6
  //     7

  // array4:
  //    1
  // 2     3
  //  4   5
};

// 测试 三种递归遍历
TEST_F(TraverseTest, TestRecursion) {
  using namespace::ds_cpp;

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  auto &str_stream = dynamic_cast<std::ostringstream &>(traverse.io());

  BiTree<int> tree1(vec3, 0);
  BiTree<int> tree2(vec4, 0);

  tree1.TraversePreOrderR(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 4 5 7 3 6 ");
  str_stream.str("");
  tree1.TraversePostOrderR(traverse);
  EXPECT_EQ(str_stream.str(), "4 7 5 2 6 3 1 ");
  str_stream.str("");
  tree1.TraverseInOrderR(traverse);
  EXPECT_EQ(str_stream.str(), "4 2 7 5 1 3 6 ");
  str_stream.str("");

  tree2.TraversePreOrderR(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 4 3 5 ");
  str_stream.str("");
  tree2.TraversePostOrderR(traverse);
  EXPECT_EQ(str_stream.str(), "4 2 5 3 1 ");
  str_stream.str("");
  tree2.TraverseInOrderR(traverse);
  EXPECT_EQ(str_stream.str(), "2 4 1 5 3 ");
  str_stream.str("");
}

// 测试 先序迭代遍历
TEST_F(TraverseTest, TestPreOrderI) {
  using namespace::ds_cpp;

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  auto &str_stream = dynamic_cast<std::ostringstream &>(traverse.io());

  BiTree<int> tree1(vec3, 0);
  BiTree<int> tree2(vec4, 0);

  tree1.TraversePreOrderI1(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 4 5 7 3 6 ");
  str_stream.str("");

  tree2.TraversePreOrderI1(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 4 3 5 ");
  str_stream.str("");

  tree1.TraversePreOrderI2(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 4 5 7 3 6 ");
  str_stream.str("");

  tree2.TraversePreOrderI2(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 4 3 5 ");
  str_stream.str("");
}
