#ifndef DS_CPP_BST_IMPL_H_
#define DS_CPP_BST_IMPL_H_

namespace ds_cpp {

template<typename T>
BST<T>::BST() : BiTree<T>(), hot_(nullptr) {}

template<typename T>
BST<T>::BST(const std::vector<T> &vec, const T &end) : BiTree<T>(vec, end), hot_(nullptr) {}

template <typename T>
typename BST<T>::BNP & BST<T>::Search(const T &e) {
  // 如果是空树 或 树根命中 则返回 root_ 引用
  if (!this->root_ || this->root_->data_ == e) {
    hot_ = nullptr;
    return this->root_;
  }

  for (hot_ = this->root_; ; ) {
    // 注意 ref 是引用, 不能作为迭代对象
    BNP &ref = e < hot_->data_ ? hot_->lc_ : hot_->rc_;
    if (!ref || ref->data_ == e) return ref;
    hot_ = ref;
  }
}

template <typename T>
typename BST<T>::BNP BST<T>::Add(const T &e) {
  BNP &p = Search(e);
  if (p) return p; // 如果存在则返回

  p = new BiNode<T>(e, hot_);
  ++this->size_;
  this->UpdateHeightAbove(p);
  return p;
}

template <typename T>
bool BST<T>::Remove(const T &e) {
  BNP &ref = Search(e);
  if (!ref) return false;

  RemoveAt(ref, hot_);
  --this->size_;
  this->UpdateHeightAbove(hot_);
  return true;
}


template <typename T>
typename BST<T>::BNP BST<T>::RemoveAt(BNP &ref, BNP &hot) {
  // 后继节点用来替换
  BNP succ = nullptr;
  // 指向被删除的节点
  BNP target = ref;

  if (!BiNode<T>::HasLc(ref)) {
    succ = ref = ref->rc_;
    if (succ) succ->parent_ = hot_;
    delete target;
    return succ;
  } else if (!BiNode<T>::HasRc(ref)) {
    succ = ref = ref->lc_;
    if (succ) succ->parent_ = hot_;
    delete target;
    return succ;
  } else {
    // 指向待删节点中序遍历后继
    target = ref->Succ();
    // 交换数值
    std::swap(target->data_, ref->data_);
    // 实际删除节点的父节点
    BNP tp= target->parent_;
    succ = target->rc_;

    // 一般实际删除节点在 父节点的左子树中
    // 除非父节点是 ref, 则删除节点在 ref 的右子树中
    if (tp == ref) {
      tp->rc_ = succ;
    } else {
      tp->lc_ = succ;
    }
    // 需要更新改动处的父节点
    hot_ = target->parent_;
    succ->parent_ = hot_;
    delete target;
    return succ;
  }
}

}  // namespace ds_cpp
#endif
