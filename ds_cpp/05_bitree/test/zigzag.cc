#include <gtest/gtest.h>
#include <sstream>

#include "bitree.h"

#define GTEST_COUT std::cout << "[---INFO---] "

TEST(ziazag, zag) {
  using namespace ds_cpp;
  std::vector<int> vec{1,
                       2, 3,
                       4, 5, 6, 7,
                       -1, -1, -1, -1, -1, -1, -1, -1};
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  tree.Zag(tree.root());
  tree.TraverseLevel(traverse);
  ASSERT_EQ(tree.root()->lc()->height(), 2);
  std::cout << oss.str() << "\n"; oss.clear(); oss.str("");



  tree.Zig(tree.root());
  tree.TraverseLevel(traverse);
  ASSERT_EQ(tree.root()->lc()->height(), 1);
  std::cout << oss.str() << "\n"; oss.clear(); oss.str("");
}
