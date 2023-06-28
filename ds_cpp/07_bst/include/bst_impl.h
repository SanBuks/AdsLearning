#ifndef DS_CPP_BST_IMPL_H_
#define DS_CPP_BST_IMPL_H_

namespace ds_cpp {

template<typename T>
BST<T>::BST() : BiTree<T>(), hot_(nullptr) {}

template<typename T>
BST<T>::BST(const std::vector<T> &vec, const T &end) : BiTree<T>(vec, end), hot_(nullptr) {}

template <typename T>
typename BST<T>::BNP & BST<T>::Search(const T &e) {
  // 如果是空树则返回 root_ 引用 或者 如果树根命中则返回 指向节点的指针引用
  if (!this->root_ || this->root_->data_ == e) {
    hot_ = nullptr;
    return this->root_;
  }
  for (hot_ = this->root_;;) {
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
  return true;
}

}  // namespace ds_cpp
#endif
