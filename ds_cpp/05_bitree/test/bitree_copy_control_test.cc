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

// 测试 插入, 删除, 获取子树大小, 更新高度操作
TEST_F(CopyControlTest, TestInsertAndRemove) {
  using namespace ds_cpp;

  BiTree<int> tree; // array3
  EXPECT_EQ(tree.Empty(), true);

  auto p1 = tree.InsertAsRoot(1);
  EXPECT_NE(p1, nullptr);
  EXPECT_EQ(p1->height(), 0);

  auto p2 = tree.InsertAsLc(p1, 2);
  EXPECT_NE(p2, nullptr);
  EXPECT_EQ(p1->height(), 1);

  auto p3 = tree.InsertAsRc(p1, 3);
  EXPECT_NE(p3, nullptr);
  EXPECT_EQ(p1->height(), 1);

  auto p4 = tree.InsertAsLc(p2, 4);
  EXPECT_NE(p4, nullptr);
  EXPECT_EQ(p1->height(), 2);

  auto p5 = tree.InsertAsRc(p2, 5);
  EXPECT_NE(p5, nullptr);
  EXPECT_EQ(p1->height(), 2);

  auto p6 = tree.InsertAsRc(p3, 6);
  EXPECT_NE(p6, nullptr);
  EXPECT_EQ(p1->height(), 2);

  auto p7 = tree.InsertAsLc(p5, 7);
  EXPECT_NE(p7, nullptr);
  EXPECT_EQ(p1->height(), 3);

  EXPECT_EQ(tree.GetSubTreeSize(p3), 2);
  EXPECT_EQ(tree.GetSubTreeSize(p2), 4);
  EXPECT_EQ(tree.size(), 7);

  EXPECT_EQ(tree.Remove(p2), 4);
  EXPECT_EQ(tree.Remove(p1), 3);
  EXPECT_EQ(tree.Empty(), true);
}

// 测试 层次遍历顺序数组构建二叉树, 层次遍历
TEST_F(CopyControlTest, TestConstructFromVector) {
  using namespace ds_cpp;

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  auto &str_stream = dynamic_cast<std::ostringstream &>(traverse.io());

  BiTree<int> tree1(vec1, 0);
  EXPECT_EQ(tree1.size(), 0);

  BiTree<int> tree2(vec2, 0);
  EXPECT_EQ(tree2.size(), 0);

  BiTree<int> tree3(vec3, 0);
  EXPECT_EQ(tree3.size(), 7);
  tree3.TraverseLevel(traverse);
  ASSERT_EQ(str_stream.str(), "1 2 3 4 5 6 7 ");
  str_stream.str("");


  BiTree<int> tree4(vec4, 0);
  EXPECT_EQ(tree4.size(), 5);
  tree4.TraverseLevel(traverse);
  ASSERT_EQ(str_stream.str(), "1 2 3 4 5 ");
  str_stream.str("");

  Vector<int> invalid_vec(array3, array_size3 - 1);
  EXPECT_THROW(BiTree<int>(invalid_vec, 0), std::runtime_error);
}

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
