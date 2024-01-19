#ifndef DS_CPP_AVL_H_
#define DS_CPP_AVL_H_

#include "bst.h"

namespace ds_cpp {

template <typename T>
class AVL : public BST<T> {

 public:
  using BNP = typename BiTree<T>::BNP;
  using SizeType = typename BiNode<T>::SizeType;

  // 理想平衡条件
  inline static bool Balanced(BNP p) { return BiNode<T>::Stature(p->lc()) == BiNode<T>::Stature(p->rc()); }
  // 平衡因子
  inline static int BalFac(BNP p) {  return BiNode<T>::Stature(p->lc()) - BiNode<T>::Stature(p->rc()); }
  // AVL 平衡条件
  inline static bool AvlBalanced(BNP p) { return (-2 < BalFac(p)) && (BalFac(p) < 2); }
  // 返回较高孩子节点, 如果相同则与 p 同侧优先
  inline static BNP TallerChild(BNP p);

  AVL();
  AVL(const std::vector<T> &vec, const T &end);

  virtual BNP Add(const T &e);
  virtual bool Remove(const T &e);

  // 按照 “3 + 4” 结构
  BNP Connect34(BNP left, BNP parent, BNP right, BNP ll, BNP lr, BNP rl, BNP rr);
  // 按照类型旋转 返回调整过后的根节点
  BNP RotateAt(BNP p);
};

}

#include "avl_impl.h"
#endif
