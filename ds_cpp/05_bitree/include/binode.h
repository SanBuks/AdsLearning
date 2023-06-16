#ifndef DS_CPP_BINODE_H
#define DS_CPP_BINODE_H

namespace ds_cpp {

template<typename T>
class BiTree;

template<typename T>
class BiNode {

  friend class BiTree<T>;

 public:
  using BNP = BiNode *;
  using SizeType = long long;

  BiNode();
  explicit BiNode(T data = T(), BNP parent = nullptr,
                  BNP lc = nullptr, BNP rc = nullptr, SizeType height = 0);

  inline T &data() { return data_; }
  inline BNP parent() { return parent_; }
  inline BNP lc() { return lc_; }
  inline BNP rc() { return rc_; }
  inline SizeType height() const { return height_; };

 private:
  // 作为左孩子插入, 如果存在左孩子则返回 nullptr
  BNP InsertAsLc(const T &data);
  // 作为右孩子插入, 如果存在有孩子则返回 nullptr
  BNP InsertAsRc(const T &data);

  // 是否是根节点
  inline static bool IsRoot(BNP p) { return !p->parent_; }
  // 是否是左孩子
  inline static bool IsLc(BNP p) { return !IsRoot(p) && p->parent_->lc_ == p; }
  // 是否是右孩子
  inline static bool IsRc(BNP p) { return !IsRoot(p) && p->parent_->rc_ == p; }
  // 是否有父节点
  inline static bool HasParent(BNP p) { return !IsRoot(p); }
  // 是否有左孩子
  inline static bool HasLc(BNP p) { return p->lc_; }
  // 是否有右孩子
  inline static bool HasRc(BNP p) { return p->rc_; }
  // 是否有孩子
  inline static bool HasC(BNP p) { return HasLc(p) || HasRc(p); }
  // 是否是叶子节点
  inline static bool IsLeaf(BNP p) { return !HasC(p); }
  // 是否有两个孩子
  inline static bool HasBc(BNP p) { return HasLc(p) && HasRc(p); }

  T data_;            // 数据
  BNP parent_;        // 指向父节点
  BNP lc_;            // 指向左孩子
  BNP rc_;            // 指向右孩子
  SizeType height_;  // 节点高度(nullptr 所指节点高度为 -1)
};

}  // namespace ds_cpp

#include "binode_impl.h"

#endif
