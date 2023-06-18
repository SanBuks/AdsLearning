#include <gtest/gtest.h>

#include "bitree.h"

#define GTEST_COUT std::cout << "[---INFO---] "


TEST(Traverse, TraversePre) {
  using namespace ds_cpp;
  using BNP = BiTree<int>::BNP;

  BiTree<int> tree;
  BNP root = tree.Insert(3);
  BNP l1 = tree.Insert(1, root);
  BNP r1 = tree.Insert(root, 2);
  BNP l1l1 = tree.Insert(3, l1);
  BNP l1r1 = tree.Insert(l1, 4);

  BiTreeTraverse<int> traverse(std::cout);
//  traverse(3);
//  tree.TraversePreRecursion(traverse);
  tree.TraversePreIteration(traverse);
}
