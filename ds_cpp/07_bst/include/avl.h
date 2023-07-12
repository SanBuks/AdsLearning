#ifndef DS_CPP_AVL_H_
#define DS_CPP_AVL_H_

#include "bst.h"

namespace ds_cpp {

template <typename T>
class AVL : public BST<T> {

 public:
  using BNP = typename BiTree<T>::BNP;
  using SizeType = typename BiNode<T>::SizeType;
  AVL();
  AVL(const std::vector<T> &vec, const T &end);

  virtual BNP Add(const T &e);
  virtual bool Remove(const T &e);

};

}

#include "avl_impl.h"
#endif
