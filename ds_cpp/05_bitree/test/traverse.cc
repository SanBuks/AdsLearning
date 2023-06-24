#include <gtest/gtest.h>
#include <sstream>

#include "bitree.h"

#define GTEST_COUT std::cout << "[---INFO---] "

TEST(Traverse, TraverseInIterationSuccession) {
  using namespace ds_cpp;
  std::vector<int> vec{1,
                       2, 3,
                       -1, 4, 5, -1,
                       6, 7, 8, 9,
                       -1, -1, 10, -1, -1, 11, -1, -1,
                       -1, -1, -1, -1};
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  tree.TraverseInIterationSuccession(traverse);
  ASSERT_EQ(oss.str(), "2 6 4 10 7 1 8 11 5 9 3 "); oss.clear(); oss.str("");


  std::vector<int> vec_empty{};
  BiTree<int> tree_empty(vec_empty, -1);
  tree_empty.TraverseInIterationSuccession(traverse);
  ASSERT_EQ(oss.str(), ""); oss.clear(); oss.str("");

  std::vector<int> vec_one{2, -1, -1};
  BiTree<int> tree_one(vec_one, -1);
  ASSERT_EQ(1, tree_one.size());
  ASSERT_EQ(0, tree_one.root()->height());
  ASSERT_EQ(2, tree_one.root()->data());
  tree_one.TraverseInIterationSuccession(traverse);
  ASSERT_EQ(oss.str(), "2 "); oss.clear(); oss.str("");
}