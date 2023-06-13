#include "bitree.h"
#include "vector.h"

#include <iostream>
#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

class ModifyTest : public ::testing::Test {
 protected:
  ModifyTest() : vec1(array1, array_size1),
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

// 测试 子树接入
TEST_F(ModifyTest, TestAttach) {
  using namespace ds_cpp;

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  auto &str_stream = dynamic_cast<std::ostringstream &>(traverse.io());

  BiTree<int> tree1(vec3, 0);
  BiTree<int> tree2(vec4, 0);
  auto p = tree1.root()->lc()->rc()->lc();
  EXPECT_EQ(p->data(), 7);
  tree1.AttachAsLc(p, tree2);
  EXPECT_EQ(tree1.size(), 12);
  EXPECT_EQ(tree2.size(), 0);
  EXPECT_EQ(tree1.root()->height(), 6);

  tree1.TraverseLevel(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 3 4 5 6 7 1 2 3 4 5 ");
  str_stream.str("");

  BiTree<int> tree3(vec3, 0);
  BiTree<int> tree4(vec4, 0);
  p = tree4.root()->rc()->lc();
  EXPECT_EQ(p->data(), 5);
  tree4.AttachAsRc(p, tree3);
  EXPECT_EQ(tree4.size(), 12);
  EXPECT_EQ(tree3.size(), 0);
  EXPECT_EQ(tree4.root()->height(), 6);

  tree4.TraverseLevel(traverse);
  EXPECT_EQ(str_stream.str(), "1 2 3 4 5 1 2 3 4 5 6 7 ");
  str_stream.str("");
}

// 测试 子树分离
TEST_F(ModifyTest, TestSecede) {
  using namespace ds_cpp;

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  auto &str_stream = dynamic_cast<std::ostringstream &>(traverse.io());

  BiTree<int> tree1(vec3, 0);
  BiTree<int> tree2(vec4, 0);

  auto p = tree1.root()->lc();
  BiTree<int> *tree3 = tree1.Secede(p);

  tree3->TraverseLevel(traverse);
  EXPECT_EQ(str_stream.str(), "2 4 5 7 ");
  str_stream.str("");
  tree1.TraverseLevel(traverse);
  EXPECT_EQ(str_stream.str(), "1 3 6 ");
  str_stream.str("");
}


