#include "gtest/gtest.h"

import ds_cpp.avl;

TEST(del, rr) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{
                 16,
          10,            25,
      -1,     11,      -1,      27,
            -1, -1,          -1, -1
  };

  Avl<int> avl(vec, -1);
  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  bool result;

  result = avl.Del(11);
  EXPECT_EQ(result , true);
  avl.TraverseLevel(traverse);
  EXPECT_EQ(avl.size(), 4);
  EXPECT_EQ(avl.root()->height(), 2);
  EXPECT_EQ(oss.str(), "16 10 25 27 "); oss.clear(); oss.str("");

  result = avl.Del(10);
  EXPECT_EQ(result, true);
  avl.TraverseLevel(traverse);
  EXPECT_EQ(avl.size(), 3);
  EXPECT_EQ(avl.root()->height(), 1);
  EXPECT_EQ(oss.str(), "25 16 27 "); oss.clear(); oss.str("");
}

TEST(del, rl) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{
               16,
       10,           25,
    -1,   11,     24,  -1,
       -1, -1,  -1, -1
  };
  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);

  Avl<int> avl(vec, -1);

  bool result;

  result = avl.Del(11);
  EXPECT_EQ(result, true);
  avl.TraverseLevel(traverse);
  EXPECT_EQ(avl.size(), 4);
  EXPECT_EQ(avl.root()->height(), 2);
  EXPECT_EQ(oss.str(), "16 10 25 24 "); oss.clear(); oss.str("");

  result = avl.Del(10);
  EXPECT_EQ(result, true);
  avl.TraverseLevel(traverse);
  EXPECT_EQ(avl.size(), 3);
  EXPECT_EQ(avl.root()->height(), 1);
  EXPECT_EQ(oss.str(), "24 16 25 "); oss.clear(); oss.str("");
}
