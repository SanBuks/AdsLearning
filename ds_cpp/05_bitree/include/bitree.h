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

  friend void swap<T>(BiTree &lhs, BiTree &rhs) noexcept;

 public:
  using typename BiNode<T>::BNP;
  using typename BiNode<T>::SizeType;

  BiTree();
  ~BiTree();
  BiTree(const BiTree &rhs) = delete;
  BiTree& operator=(const BiTree &rhs) = delete;

  // 三种插入方式 (原没有)
  BNP InsertAsRoot(const T &data);
  BNP InsertAsLc(BNP p, const T &data);
  BNP InsertAsRc(BNP p, const T &data);

  inline SizeType size() const { return size_; }
  inline BNP root() { return root_; }
  inline bool Empty() const { return !size_; }

 protected:
  // 根据孩子节点高度更新 p 节点高度
  void virtual UpdateHeight(BNP p);
  // 更新 p 节点及祖先节点高度
  void UpdateAbove(BNP p);

  BNP root_;
  SizeType size_;

 private:

};

}  // namespace ds_cpp

#include "bitree_impl.h"

#endif
