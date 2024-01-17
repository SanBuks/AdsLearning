export module ds_cpp.bitree:binode;

import :common;

export namespace ds_cpp {

template<typename T> class BiTree;

// 节点类 含父节点
template<typename T>
class BiNode {

  friend class BiTree<T>;

 public:
  using SizeType = BiTreeType::SizeType;  // 无符号数量类型
  using BNP = BiNode *;                   // 节点指针类型

  explicit BiNode(T data = T(), BNP parent = nullptr, BNP lc = nullptr, BNP rc = nullptr, SizeType height = 0)
      : data_(data),
        parent_(parent),
        lc_(lc),
        rc_(rc),
        height_(height) {}
  BiNode(const BiNode &rhs) = delete;
  BiNode(BiNode &&rhs) = delete;
  BiNode &operator=(const BiNode &rhs) = delete;
  BiNode &operator=(BiNode &&rhs) = delete;
  ~BiNode() = default;

  [[nodiscard]] inline T &data() { return data_; }
  [[nodiscard]] inline BNP parent() { return parent_; }
  [[nodiscard]] inline BNP lc() { return lc_; }
  [[nodiscard]] inline BNP rc() { return rc_; }
  [[nodiscard]] inline SizeType height() const { return height_; };

  [[nodiscard]] inline static bool HasParent(BNP p) { return p->parent_; }
  [[nodiscard]] inline static bool HasLc(BNP p) { return p->lc_; }
  [[nodiscard]] inline static bool HasRc(BNP p) { return p->rc_; }
  [[nodiscard]] inline static bool HasC(BNP p) { return HasLc(p) || HasRc(p); }
  [[nodiscard]] inline static bool HasBc(BNP p) { return HasLc(p) && HasRc(p); }

  [[nodiscard]] inline static bool IsRoot(BNP p) { return !HasParent(p); }
  [[nodiscard]] inline static bool IsLc(BNP p) { return HasParent(p) && p->parent_->lc_ == p; }
  [[nodiscard]] inline static bool IsRc(BNP p) { return HasParent(p) && p->parent_->rc_ == p; }
  [[nodiscard]] inline static bool IsLeaf(BNP p) { return !HasC(p); }
  [[nodiscard]] inline static SizeType Height(BNP p) { return p ? p->height_ : 0; }

  [[nodiscard]] BNP InsertAsLc(const T &data);  // 插入到左孩子
  [[nodiscard]] BNP InsertAsRc(const T &data);  // 插入到右孩子
  [[nodiscard]] SizeType Size();                // 子树节点数量
  [[nodiscard]] BNP Successor();                // 中序遍历的后继节点

 private:
  T data_{};            // 数据
  BNP parent_{};        // 指向父节点
  BNP lc_{};            // 指向左孩子
  BNP rc_{};            // 指向右孩子
  SizeType height_{};   // 节点高度
};

template<typename T>
typename BiNode<T>::BNP BiNode<T>::InsertAsLc(const T &data) {
  if (!lc_) {
    lc_ = new BiNode(data, this);
    return lc_;
  } else {
    return nullptr;
  }
}

template<typename T>
typename BiNode<T>::BNP BiNode<T>::InsertAsRc(const T &data) {
  if (!rc_) {
    rc_ = new BiNode(data, this);
    return rc_;
  } else {
    return nullptr;
  }
}

template<typename T>
typename BiNode<T>::SizeType BiNode<T>::Size() {
  SizeType size = 1;
  if (lc_) size += lc_->Size();
  if (rc_) size += rc_->Size();
  return size;
}

template<typename T>
typename BiNode<T>::BNP BiNode<T>::Successor() {
  auto p = this;

  // 如果存在右孩子, 则返回左藤树最左下的节点
  if (p->rc_) {
    p = p->rc_;
    while (p->lc_) p = p->lc_;
  } else {
    // 如果没有右孩子, 则找到指定父亲节点(父亲节点是爷爷节点的左孩子)
    // 极端情况找到根节点, 根节点不是右孩子则返回根节点的父节点
    while (IsRc(p)) p = p->parent_;
    p = p->parent_;
  }
  return p;
}

}
