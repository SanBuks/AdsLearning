#include "gtest/gtest.h"
#include <sstream>

import ds_cpp.bst;

// leetcode_0450
TEST(bst, del_empty) {
  using namespace std;
  using namespace ds_cpp;

  Bst<int> bst;
  EXPECT_EQ(bst.Del(3), true);
}

TEST(bst, del_one) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                     10,     25,
                  -1,  11, -1,  26,
                     -1, -1,  -1, -1};

  Bst<int> bst(vec, -1);
  ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  EXPECT_EQ(bst.Del(25), true);
  EXPECT_EQ(4, bst.size());
  EXPECT_EQ(2, bst.root()->height());

  bst.TraverseIn(traverse);
  EXPECT_EQ(oss.str(), "10 11 16 26 "); oss.str(""); oss.clear();
}

TEST(bst, del_two_right) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                    10,     25,
                 -1,  11, -1,  26,
                    -1, -1,  -1, -1};
  Bst<int> bst(vec, -1);
  ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  EXPECT_EQ(bst.Del(16), true);
  EXPECT_EQ(4, bst.size());
  EXPECT_EQ(2, bst.root()->height());
  bst.TraverseIn(traverse);
  EXPECT_EQ(oss.str(), "10 11 25 26 "); oss.str(""); oss.clear();
}

TEST(bst, del_two_left) {
  using namespace std;
  using namespace ds_cpp;
  vector<int> vec{       16,
                    10,     25,
                 -1,  11, 17,  26,
                    -1, -1,  -1, -1};
  Bst<int> bst(vec, -1);
  ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  EXPECT_EQ(bst.Del(16), true);
  EXPECT_EQ(5, bst.size());
  EXPECT_EQ(2, bst.root()->height());
  bst.TraverseIn(traverse);
  EXPECT_EQ(oss.str(), "10 11 17 25 26 "); oss.str(""); oss.clear();
}
