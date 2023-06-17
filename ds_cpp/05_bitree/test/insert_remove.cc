#include <gtest/gtest.h>

#include "bitree.h"

#define GTEST_COUT std::cout << "[---INFO---] "

TEST(ConstructTest, InsertAndRemove1) {
  using namespace ds_cpp;
  using BNP = BiTree<int>::BNP;

  BiTree<int> tree;
  BNP root = tree.Insert(3);

  ASSERT_EQ(1, tree.size());
  ASSERT_EQ(3, root->data());
  ASSERT_EQ(0, root->height());
  ASSERT_EQ(tree.Remove(root), 1);
  ASSERT_EQ(tree.Empty(), true);
}


TEST(ConstructTest, InsertAndRemove2) {
  using namespace ds_cpp;
  using BNP = BiTree<int>::BNP;

  BiTree<int> tree;
  BNP root = tree.Insert(3);
  BNP l1 = tree.Insert(1, root);
  BNP r1 = tree.Insert(root, 2);
  BNP l1l1 = tree.Insert(3, l1);
  BNP l1r1 = tree.Insert(l1, 4);

  ASSERT_EQ(5, tree.size());
  ASSERT_EQ(2, root->height());
  ASSERT_EQ(3, tree.Remove(l1));
  ASSERT_EQ(2, tree.size());
}

TEST(ConstructTest, Destruction) {
  using namespace ds_cpp;
  using BNP = BiTree<int>::BNP;

  BiTree<int> tree;
  BNP root = tree.Insert(3);
  BNP l1 = tree.Insert(1, root);
  BNP r1 = tree.Insert(root, 2);
  BNP l1l1 = tree.Insert(3, l1);
  BNP l1r1 = tree.Insert(l1, 4);

  ASSERT_EQ(5, tree.Remove(tree.root()));
  ASSERT_EQ(nullptr, tree.root());
  ASSERT_EQ(true, tree.Empty());
}
