#ifndef DS_CPP_BINODE_H
#define DS_CPP_BINODE_H

namespace ds_cpp {

template<typename T>
class BiTree;

template<typename T>
class BST;

template<typename T>
class BiNode {

  friend class BiTree<T>;
  friend class BST<T>;

 public:
  using BNP = BiNode *;
  using SizeType = long long;

  BiNode();
  explicit BiNode(const T &data = T(),
                  BNP parent = nullptr, BNP lc = nullptr, BNP rc = nullptr,
                  SizeType height = 0);

  inline T &data() { return data_; }
  inline BNP parent() { return parent_; }
  inline BNP lc() { return lc_; }
  inline BNP rc() { return rc_; }
  inline SizeType height() const { return height_; };

  // 递归计算子树规模
  SizeType Size();
  // 返回中序遍历的后继节点
  BNP Succ();

 private:
  // 作为左孩子插入, 如果存在左孩子则返回 nullptr
  BNP InsertAsLc(const T &data);
  // 作为右孩子插入, 如果存在有孩子则返回 nullptr
  BNP InsertAsRc(const T &data);

  inline static bool IsRoot(BNP p) { return !p->parent_; }
  inline static bool IsLc(BNP p) { return !IsRoot(p) && p->parent_->lc_ == p; }
  inline static bool IsRc(BNP p) { return !IsRoot(p) && p->parent_->rc_ == p; }
  inline static bool HasParent(BNP p) { return !IsRoot(p); }
  inline static bool HasLc(BNP p) { return p->lc_; }
  inline static bool HasRc(BNP p) { return p->rc_; }
  inline static bool HasC(BNP p) { return HasLc(p) || HasRc(p); }
  inline static bool IsLeaf(BNP p) { return !HasC(p); }
  inline static bool HasBc(BNP p) { return HasLc(p) && HasRc(p); }

  /**
   * @param p 需要分离的子树根, 作为媒介访问不需要是引用
   * @param root 被分离的子树根指针, 有可能分离整棵树, 需要是引用
   * @retrun 需要修改的引用对象
   */
  inline static BNP &FromParentTo(BNP p, BNP &root) {
    return IsRoot(p) ? root : IsLc(p) ? p->parent_->lc_ : p->parent_->rc_;
  }

  T data_;            // 数据
  BNP parent_;        // 指向父节点
  BNP lc_;            // 指向左孩子
  BNP rc_;            // 指向右孩子
  SizeType height_;   // 节点高度(nullptr 所指节点高度为 -1)
};

}  // namespace ds_cpp

#include "binode_impl.h"

#endif
