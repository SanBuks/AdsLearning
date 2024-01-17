#include <gtest/gtest.h>
#include <sstream>

import ds_cpp.bitree;

// 修改相关
// BNP Attach(BiTree<T> &tree, BNP p);  // 接入左子树
// BNP Attach(BNP p, BiTree<T> &tree);  // 接入左子树
// BiTree *Secede(BNP p);               // 分离子树

TEST(edit, attach_left) {
  using namespace ds_cpp;
  using BNP = BiTree<int>::BNP;


  std::vector<int> vec{
          1,
     2,        3,
  -1, -1,   -1, -1
  };

  BiTree<int> tree(vec, -1);
  BiTree<int> attached_tree(vec, -1);
  auto left = tree.root()->lc();
  auto p = tree.Attach(attached_tree, left);

  ASSERT_EQ(p->data(), 1);

  ASSERT_EQ(attached_tree.size(), 0);
  ASSERT_EQ(attached_tree.root(), nullptr);

  ASSERT_EQ(tree.size(), 6);
  ASSERT_EQ(tree.root()->height(), 3);

  std::ostringstream oss;
  BiTreeTraverse<int> vst(oss);
  tree.TraverseLevel(vst);
  ASSERT_EQ(oss.str(), "1 2 3 1 2 3 "); oss.clear(); oss.str("");
}

TEST(edit, attach_right) {
  using namespace ds_cpp;
  using BNP = BiTree<int>::BNP;

  std::vector<int> vec{
          1,
     2,        3,
  -1, -1,   -1, -1
  };


  BiTree<int> tree(vec, -1);
  BiTree<int> attached_tree(vec, -1);
  auto right = tree.root()->rc();
  auto p = tree.Attach(right, attached_tree);

  ASSERT_EQ(p->data(), 1);

  ASSERT_EQ(attached_tree.size(), 0);
  ASSERT_EQ(attached_tree.root(), nullptr);

  ASSERT_EQ(tree.size(), 6);
  ASSERT_EQ(tree.root()->height(), 3);

  std::ostringstream oss;
  BiTreeTraverse<int> vst(oss);
  tree.TraverseLevel(vst);
  ASSERT_EQ(oss.str(), "1 2 3 1 2 3 "); oss.clear(); oss.str("");
}

TEST(edit, secede) {
  using namespace ds_cpp;
  using BNP = BiTree<int>::BNP;

  std::vector<int> vec{
          1,
     2,        3,
  -1, -1,   -1, -1
  };


  BiTree<int> tree(vec, -1);
  auto r = tree.root();
  auto seceded_tree = tree.Secede(r);

  ASSERT_EQ(seceded_tree->root()->data(), 1);

  ASSERT_EQ(seceded_tree->size(), 3);
  ASSERT_EQ(tree.size(), 0);
  ASSERT_EQ(tree.root(), nullptr);

  std::ostringstream oss;
  BiTreeTraverse<int> vst(oss);
  seceded_tree->TraverseLevel(vst);
  ASSERT_EQ(oss.str(), "1 2 3 "); oss.clear(); oss.str("");
  delete seceded_tree;
}