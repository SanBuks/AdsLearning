#include <gtest/gtest.h>
#include <sstream>

import ds_cpp.bitree;

// 类相关:
// class BiNode;         // 内部节点类
// class BiTreeTraverse; // 遍历调用对象

// 构建相关:
// void BuildFromLevel(const std::vector<T> &vec, const T &null); // 层次遍历构建二叉树
// BNP Insert(const T &data);          // 插入根
// BNP Insert(const T &data, BNP p);   // 插入左孩子, 更新高度
// BNP Insert(BNP p, const T &data);   // 插入右孩子, 更新高度
// void UpdateHeightAbove(BNP p);      // 更新高度

// 析构相关
// SizeType Remove(BNP p);             // 删除子树
// static SizeType RemoveAt(BNP p);    // 递归删除子树所有节点, 返回删除节点个数
// static BNP &Ref(BNP p, BNP &root);  // 返回父节点对 p 的引用, 如果是根节点则返回 root 引用

// 遍历相关
// template <typename VST> void TraverseLevel(const VST &visit);  // 层次遍历

// leetcode_0102
TEST(construct, construct_from_vector) {
  using namespace ds_cpp;
  std::vector<int> vec{            1,
                     2,                             3,
              -1,           4,             5,                 -1,
                      6,        7,      8,         9,
                   -1, -1,   10,  -1, -1, 11,   -1, -1,
                           -1, -1,      -1, -1
  };
  BiTree<int> tree(vec, -1);

  std::ostringstream oss;
  BiTreeTraverse<int> traverse(oss);
  tree.TraverseLevel(traverse);
  ASSERT_EQ(oss.str(), "1 2 3 4 5 6 7 8 9 10 11 "); oss.clear(); oss.str("");
  ASSERT_EQ(tree.root()->height(), 4);
  ASSERT_EQ(tree.root()->Size(), 11);
}