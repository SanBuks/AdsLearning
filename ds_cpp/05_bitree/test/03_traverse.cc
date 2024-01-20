#include <gtest/gtest.h>
#include <sstream>

import ds_cpp.bitree;

// leetcode_0144
TEST(traverse, pre) {
  using namespace ds_cpp;
  std::vector<int> vec{            1,
                     2,                             3,
              -1,           4,             5,                 -1,
                      6,        7,      8,         9,
                   -1, -1,   10,  -1, -1, 11,   -1, -1,
                           -1, -1,      -1, -1
  };
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  tree.TraversePre(traverse);
  ASSERT_EQ(oss.str(), "1 2 4 6 7 10 3 5 8 11 9 "); oss.clear(); oss.str("");

  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "1 2 3 4 5 6 7 8 9 10 11 "); oss.clear(); oss.str("");
}

// leetcode_0094
TEST(traverse, in) {
  using namespace ds_cpp;
  std::vector<int> vec{            1,
                     2,                             3,
              -1,           4,             5,                 -1,
                      6,        7,      8,         9,
                   -1, -1,   10,  -1, -1, 11,   -1, -1,
                           -1, -1,      -1, -1
  };
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  tree.TraverseIn(traverse);
  ASSERT_EQ(oss.str(), "2 6 4 10 7 1 8 11 5 9 3 "); oss.clear(); oss.str("");

  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "1 2 3 4 5 6 7 8 9 10 11 "); oss.clear(); oss.str("");
}

TEST(traverse, in_backtrace) {
  using namespace ds_cpp;
  std::vector<int> vec{            1,
                     2,                             3,
              -1,           4,             5,                 -1,
                      6,        7,      8,         9,
                   -1, -1,   10,  -1, -1, 11,   -1, -1,
                           -1, -1,      -1, -1
  };
  BiTree<int> tree(vec, -1);
  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  tree.TraverseIn(traverse);
  ASSERT_EQ(oss.str(), "2 6 4 10 7 1 8 11 5 9 3 "); oss.clear(); oss.str("");

  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "1 2 3 4 5 6 7 8 9 10 11 "); oss.clear(); oss.str("");
}

// leetcode_0145
TEST(traverse, post) {
  using namespace ds_cpp;
  std::vector<int> vec{            1,
                     2,                             3,
              -1,           4,             5,                 -1,
                      6,        7,      8,         9,
                   -1, -1,   10,  -1, -1, 11,   -1, -1,
                           -1, -1,      -1, -1
  };
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  tree.TraversePost(traverse);
  ASSERT_EQ(oss.str(), "6 10 7 4 2 11 8 9 5 3 1 "); oss.clear(); oss.str("");

  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "1 2 3 4 5 6 7 8 9 10 11 "); oss.clear(); oss.str("");
}

TEST(traverse, post2) {
  using namespace ds_cpp;
  std::vector<int> vec{            1,
                     -1,                             2,
                                          3,                 -1,
                                       -1, -1
  };
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  tree.TraversePost(traverse);
  ASSERT_EQ(oss.str(), "3 2 1 "); oss.clear(); oss.str("");

  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "1 2 3 "); oss.clear(); oss.str("");
}
