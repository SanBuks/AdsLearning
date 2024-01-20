#include <sstream>
#include <gtest/gtest.h>

import ds_cpp.bst;

// leetcode_0700
TEST(search, empty) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{};
  Bst<int> bst(vec, -1);
  auto &p = bst.SearchRef(9);
  EXPECT_EQ(p, nullptr);
}

TEST(search, root) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{9, -1, -1};

  Bst<int> bst(vec, -1);
  auto &p = bst.SearchRef(9);
  EXPECT_EQ(p->data(), 9);
}

TEST(search, normal) {
  using namespace std;
  using namespace ds_cpp;

  vector<int> vec{       16,
                  10,          25,
              -1,    11,   -1,      26,
                  -1, -1,         -1, -1};

  Bst<int> bst(vec, -1);
  auto &p = bst.SearchRef(26);
  EXPECT_EQ(p->data(), 26);
  EXPECT_EQ(bst.pcache()->data(), 25);
  bst.Insert(17, p);

  stringstream oss;
  BiTreeTraverse<int> traverse(oss);
  bst.TraverseLevel(traverse);
  EXPECT_EQ(oss.str(), "16 10 25 11 26 17 "); oss.clear(); oss.str("");
}

