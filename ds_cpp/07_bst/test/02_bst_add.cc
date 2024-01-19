#include <sstream>
#include "gtest/gtest.h"

import ds_cpp.bst;

TEST(bst, add_one) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                     10,     25,
                  -1,  11, -1, 26,
                     -1, -1, -1, -1};

  Bst<int> bst(vec, -1);
  bst.Add(9);
  ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  bst.TraverseLevel(traverse);
  EXPECT_EQ(oss.str(), "16 10 25 9 11 26 ");
  EXPECT_EQ(bst.root()->height(), 2);
}

TEST(bst, add_tree) {
  using namespace std;
  using namespace ds_cpp;

  Bst<int> bst;
  bst.Add(16);
  bst.Add(10);
  bst.Add(11);
  bst.Add(25);
  bst.Add(9);
  bst.Add(26);

  ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  bst.TraverseLevel(traverse);
  EXPECT_EQ(oss.str(), "16 10 25 9 11 26 "); oss.str(""); oss.clear();
  EXPECT_EQ(bst.root()->height(), 2);

  bst.TraverseIn(traverse);
  EXPECT_EQ(oss.str(), "9 10 11 16 25 26 "); oss.str(""); oss.clear();
}

