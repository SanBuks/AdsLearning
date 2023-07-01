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

  for (hot_ = this->root_;;) {
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
  BNP succ = nullptr;
  BNP target = ref;

  if (!BiNode<T>::HasLc(ref)) {
    succ = ref = ref->rc_;
  } else if (!BiNode<T>::HasRc(ref)) {
    succ = ref = ref->lc_;
  } else {
    target = ref->Succ();
    std::swap(target->data_, target->data_);
    BNP target_parent = target->parent_;
    if (target_parent == ref) {
      target_parent->rc_ = succ = target->rc_;
    } else {
      target_parent->lc_ = succ = target->rc_;
    }
  }
  hot_ = target->parent_;
  if (succ) succ->parent_ = hot_;
  delete target;
  return succ;
}

}  // namespace ds_cpp
#endif
