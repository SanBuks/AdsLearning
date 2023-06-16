#ifndef DS_CPP_BITREE_H
#define DS_CPP_BITREE_H

#include "binode.h"
#include "bitree_error.h"

#include <vector>
#include <queue>
#include <stack>

namespace ds_cpp {

template<typename>
class BiTree;

template<typename T>
void swap(BiTree<T> &lhs, BiTree<T> &rhs) noexcept;

template<typename T>
class BiTree {

  friend void swap(BiTree<T> &lhs, BiTree<T> &rhs) noexcept;

 public:
  using typename BiNode<T>::BNP;
  using typename BiNode<T>::SizeType;

  BiTree();
  ~BiTree();

  // 返回元素数量
  inline SizeType size() const { return size_; }
  // 返回根节点
  inline BNP root() { return root_; }
  // 是否为空
  inline bool Empty() const { return !size_; }

 protected:
  BNP root_;
  SizeType size_;

};


}  // namespace ds_cpp

#include "bitree_impl.h"

#endif
