#ifndef DS_CPP_BST_H_
#define DS_CPP_BST_H_

#include "bitree.h"

namespace ds_cpp {

template<typename T>
class BST : public BiTree<T> {

 public:
  using BNP = typename BiTree<T>::BNP;
  using SizeType = typename BiNode<T>::SizeType;

  BST();
  BST(const std::vector<T> &vec, const T &end);

  // 查找指向节点的指针引用
  virtual BNP &Search(const T &e);
  // 插入节点(唯一)
  virtual BNP Add(const T &e);
  // 删除节点
  virtual bool Remove(const T &e);

 protected:
  //命中节点的父亲
  BNP hot_;
  // 在
  BNP RemoveAt(BNP &ref);
};

}  // namespace ds_cpp

#include "bst_impl.h"

#endif
