#include <gtest/gtest.h>
#include <sstream>

#include "bitree.h"

#define GTEST_COUT std::cout << "[---INFO---] "

TEST(construct, construct_from_vector) {
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

  tree.TraversePreIteration(traverse);
  ASSERT_EQ(oss.str(), "1 2 4 6 7 10 3 5 8 11 9 "); oss.clear(); oss.str("");

  tree.TraverseInIterationVine(traverse);
  ASSERT_EQ(oss.str(), "2 6 4 10 7 1 8 11 5 9 3 "); oss.clear(); oss.str("");
  tree.TraverseInIteration(traverse);
  ASSERT_EQ(oss.str(), "2 6 4 10 7 1 8 11 5 9 3 "); oss.clear(); oss.str("");

  tree.TraversePostIteration(traverse);
  ASSERT_EQ(oss.str(), "6 10 7 4 2 11 8 9 5 3 1 "); oss.clear(); oss.str("");
  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "1 2 3 4 5 6 7 8 9 10 11 "); oss.clear(); oss.str("");

  ASSERT_EQ(tree.root()->height(), 4);
  ASSERT_EQ(tree.root()->Size(), 11);
}