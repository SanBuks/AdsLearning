#include <gtest/gtest.h>
#include <sstream>

import ds_cpp.bitree;

TEST(ziazag, zig) {
  using namespace ds_cpp;
  std::vector<int> vec{
                          1,
              2,                    3,
       4,            5,       6,           7,
    -1, -1,       -1, -1,   -1, -1,      -1, -1
  };
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  auto r = tree.root();

  auto p = tree.Zig(r);
//                           2,
//              4,                     1,
//      -1,            -1,       5,           3,
//                            -1, -1,     6,      7,
//                                     -1, -1, -1,  -1
  if (r == p) FAIL();
  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "2 4 1 5 3 6 7 "); oss.clear(); oss.str("");
  ASSERT_EQ(tree.root()->height(), 3);
  ASSERT_EQ(tree.root()->rc()->height(), 2);
}

TEST(ziazag, zag) {
  using namespace ds_cpp;
  std::vector<int> vec{
                          1,
              2,                    3,
       4,            5,       6,           7,
    -1, -1,       -1, -1,   -1, -1,      -1, -1
  };
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  auto r = tree.root();
  auto p = tree.Zig(r);
  auto q = tree.Zag(p);

  if (q == p) FAIL();
  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "1 2 3 4 5 6 7 "); oss.clear(); oss.str("");
  ASSERT_EQ(tree.root()->height(), 2);
  ASSERT_EQ(tree.root()->rc()->height(), 1);
}