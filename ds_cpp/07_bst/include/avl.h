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
  inline static bool TallerChild(BNP p) {
    if (BiNode<T>::Stature(p->lc()) > BiNode<T>::Stature(p->rc())) {
      return p->lc();
    } else if (BiNode<T>::Stature(p->lc()) < BiNode<T>::Stature(p->rc())) {
      return p->rc();
    } else {
      return BiNode<T>::IsLc(p) ? p->lc() : p->rc();
    }
  }

  AVL();
  AVL(const std::vector<T> &vec, const T &end);

  virtual BNP Add(const T &e);
  virtual bool Remove(const T &e);

};

}

#include "avl_impl.h"
#endif
