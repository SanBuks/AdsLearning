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
  using BNP = typename BiNode<T>::BNP;
  using SizeType = typename BiNode<T>::SizeType;

  BiTree();
  BiTree(const std::vector<T> &vec, const T &end);
  ~BiTree();
  BiTree(const BiTree &rhs) = delete;
  BiTree& operator=(const BiTree &rhs) = delete;

  /// 三种节点初始化
  BNP Insert(const T &data);         // 根
  BNP Insert(const T &data, BNP p);  // 左孩子
  BNP Insert(BNP p, const T &data);  // 右孩子

  /// 两种接入子树
  BNP Attach(BiTree<T> &tree, BNP p); // 接入左子树
  BNP Attach(BNP p, BiTree<T> &tree); // 接入右子树

  /// 删除/分离
  SizeType Remove(BNP p);   // 删除子树
  SizeType static RemoveAt(BNP p); // 递归删除子树
  BiTree *Secede(BNP p);    // 分离子树, p 一定指向本树中的节点

  /// 遍历方式
  // 先序遍历
  template <typename VST>
  void TraversePreIteration(const VST &visit);
  // 中序遍历
  template <typename VST>
  void TraverseInIterationVine(const VST &visit);
  template <typename VST>
  void TraverseInIteration(const VST &visit);
  template <typename VST>
  void TraverseInIterationSuccession(const VST &visit);
  // 后序遍历
  template <typename VST>
  void TraversePostIteration(const VST &visit);
  // 层次遍历
  template <typename VST>
  void TraverseLevel(const VST &visit);

  inline SizeType size() const { return size_; }
  inline BNP root() { return root_; }
  inline bool Empty() const { return !size_; }

 protected:
  // 更新 p 节点及祖先节点高度
  void UpdateHeightAbove(BNP p);

  BNP root_;
  SizeType size_;

 private:
  // 根据孩子节点高度更新 p 节点高度
  void virtual UpdateHeight(BNP p);

  template <typename VST>
  void TraversePreIteration(BNP p, const VST &visit);
  template <typename VST>
  void TraverseInIterationVine(BNP p, const VST &visit);
  template <typename VST>
  void TraverseInIterationSuccession(BNP p, const VST &visit);
  template <typename VST>
  void TraverseInIteration(BNP p, const VST &visit);
  template <typename VST>
  void TraversePostIteration(BNP p, const VST &visit);
  template <typename VST>
  void TraverseLevel(BNP p, const VST &visit);
};

}  // namespace ds_cpp

#include "bitree_impl.h"

#endif
