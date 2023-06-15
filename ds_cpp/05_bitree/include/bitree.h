#ifndef DS_CPP_BITREE_H
#define DS_CPP_BITREE_H

#include "binode.h"
#include "bitree_error.h"

#include <vector>
#include <queue>
#include <stack>

namespace ds_cpp {

template <typename>
class BiTree;

template <typename T>
void swap(BiTree<T> &lhs, BiTree<T> &rhs) noexcept;

template <typename T>
class BiTree {

 public:
  using BNP = BiNode<T> *;
  BiTree();
 private:
  BNP root_;
  long long size_;

};


}  // namespace ds_cpp

#endif
