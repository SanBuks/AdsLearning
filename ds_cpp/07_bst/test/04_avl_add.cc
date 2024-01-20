#include "gtest/gtest.h"

import ds_cpp.avl;

TEST(avl, insert_rr) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                     10,     25,
                  -1,  11, -1, 27,
                     -1, -1, -1, -1};
  Avl<int> avl(vec, -1);
  auto p = avl.Add(28);
  EXPECT_EQ(p->data(), 28);
  EXPECT_EQ(p->height(), 0);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  avl.TraverseLevel(traverse);
  EXPECT_EQ(oss.str(), "16 10 27 11 25 28 "); oss.clear(); oss.str("");
  EXPECT_EQ(avl.root()->height(), 2);
}

TEST(avl, insert_rl) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                     10,     25,
                  -1,  11, -1, 27,
                     -1, -1, -1, -1};


  Avl<int> avl(vec, -1);
  auto p = avl.Add(26);
  EXPECT_EQ(p->data(), 26);
  EXPECT_EQ(p->height(), 1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  avl.TraverseLevel(traverse);
  EXPECT_EQ(oss.str(), "16 10 26 11 25 27 "); oss.clear(); oss.str("");
  EXPECT_EQ(avl.root()->height(), 2);
}

