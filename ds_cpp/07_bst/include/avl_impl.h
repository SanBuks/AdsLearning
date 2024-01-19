#ifndef DS_CPP_AVL_IMPL_H_
#define DS_CPP_AVL_IMPL_H_

namespace ds_cpp {

template <typename T>
AVL<T>::AVL() : BST<T>() {}

template<typename T>
AVL<T>::AVL(const std::vector<T> &vec, const T &end) : BST<T>(vec, end) {}

template<typename T>
typename AVL<T>::BNP AVL<T>::TallerChild(BNP p) {
  if (!p) return nullptr;

  int lh = BiNode<T>::Stature(p->lc());
  int rh = BiNode<T>::Stature(p->rc());
  if (lh > rh) {
    return p->lc();
  } else if (lh < rh) {
    return p->rc();
  } else {
    return BiNode<T>::IsLc(p) ? p->lc() : p->rc();
  }
}

template<typename T>
typename AVL<T>::BNP AVL<T>::Add(const T &e) {
  // 查找插入位置, 如果节点存在则直接返回
  BNP &insert_ref = this->Search(e);
  if (insert_ref) return insert_ref;

  // 创建节点
  insert_ref = new BiNode<T>(e, this->hot_); ++this->size_;
  BNP pos = insert_ref;

  // 遍历祖先调整平衡和高度
  for (BNP g = insert_ref; g; g = g->parent()) {
    if (!AvlBalanced(g)){
      // 找到 最高孩子节点的最高孩子节点
      BNP v = TallerChild(TallerChild(g));
      BNP &ref = this->FromParentTo(g);
      BNP parent = this->RotateAt(v);
      ref = parent;
      break;
    } else {
      this->UpdateHeight(g);
    }
  }
  return pos;
}

template<typename T>
bool AVL<T>::Remove(const T &e) {
  BNP &remove_ref = this->Search(e);
  if (!remove_ref) return false;
  this->BST<T>::RemoveAt(remove_ref); --this->size_;
  for (BNP g = this->hot_; g; g = g->parent_) {
    if (!AvlBalanced(g)) {
      BNP v = TallerChild(TallerChild(g));
      BNP &ref = this->FromParentTo(g);
      BNP parent = RotateAt(v);
      ref = parent;
    }
    this->UpdateHeight(g);
  }
  return true;
}

template<typename T>
typename AVL<T>::BNP AVL<T>::Connect34(BNP left, BNP parent, BNP right,
                                       BNP ll, BNP lr, BNP rl, BNP rr) {
  // 处理 "4" 个关系
  left->lc_ = ll; if (ll) ll->parent_ = left;
  left->rc_ = lr; if (lr) lr->parent_ = left;
  right->lc_ = rl; if (rl) rl->parent_ = right;
  right->rc_ = rr; if (rr) rr->parent_ = right;

  // 处理 "3" 个节点
  parent->lc_ = left; left->parent_ = parent;
  parent->rc_ = right; right->parent_ = parent;

  // 更新高度
  this->UpdateHeight(left);
  this->UpdateHeight(right);
  this->UpdateHeight(parent);

  return parent;
}

template<typename T>
typename AVL<T>::BNP AVL<T>::RotateAt(BNP v) {
  BNP p = v->parent_;
  BNP g = p->parent_;
  if (BiNode<T>::IsLc(p)) {
    if (BiNode<T>::IsLc(v)) { // LL
      p->parent_ = g->parent_;
      return Connect34(v, p, g, v->lc_, v->rc_, p->rc_, g->rc_);
    } else { // LR
      v->parent_ = g->parent_;
      return Connect34(p, v, g, p->lc_, v->lc_, v->rc_, g->rc_);
    }
  } else {
    if (BiNode<T>::IsRc(v)) { // RR
      p->parent_ = g->parent_;
      return Connect34(g, p, v, g->lc_, p->lc_, v->lc_, v->rc_);
    } else { // RL
      v->parent_ = g->parent_;
      return Connect34(g, v, p, g->lc_, v->lc_, v->rc_, p->rc_);
    }
  }
}


}

#endif
