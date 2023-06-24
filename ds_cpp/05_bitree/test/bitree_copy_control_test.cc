#include "bitree.h"
#include "vector.h"

#include <iostream>
#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

class CopyControlTest : public ::testing::Test {
 protected:
  CopyControlTest() : vec1(array1, array_size1),
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



// 测试 拷贝构造, 赋值, 移动拷贝构造, 移动赋值, 交换操作
TEST_F(CopyControlTest, TestCopyControl) {
  using namespace ds_cpp;

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  auto &str_stream = dynamic_cast<std::ostringstream &>(traverse.io());

  BiTree<int> tree1(vec1, 0);
  BiTree<int> tree3(vec3, 0);
  BiTree<int> tree4(vec4, 0);

  // 测试 拷贝构造
  BiTree<int> t_tree1(tree3);
  t_tree1.TraverseLevel(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 3 4 5 6 7 ");
  str_stream.str("");

  // 测试 赋值
  t_tree1 = tree4;
  t_tree1.TraverseLevel(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 3 4 5 ");
  str_stream.str("");

  // 测试 移动拷贝构造
  BiTree<int> t_tree2(std::move(tree3));
  t_tree2.TraverseLevel(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 3 4 5 6 7 ");
  str_stream.str("");
  EXPECT_EQ(tree3.size(), 0);

  // 测试 移动赋值
  t_tree2 = std::move(tree4);
  t_tree2.TraverseLevel(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 3 4 5 ");
  str_stream.str("");
  EXPECT_EQ(tree4.size(), 0);
}
