#ifndef DS_CPP_BITREE_IMPL_H_
#define DS_CPP_BITREE_IMPL_H_

namespace ds_cpp {

template<typename T>
void swap(BiTree<T> &lhs, BiTree<T> &rhs) noexcept {
  using std::swap;
  swap(lhs.root_, rhs.root_);
  swap(lhs.size_, rhs.size_);
}

template<typename T>
BiTree<T>::BiTree() : size_(0), root_(nullptr) {}

template<typename T>
BiTree<T>::~BiTree() = default;

template<typename T>
typename BiTree<T>::BNP BiTree<T>::InsertAsRoot(const T &data) {
  if (root_) { return nullptr; }
  root_ = new BiNode<T>(data, nullptr);
  size_ = 1;
  return root_;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::InsertAsLc(BNP p, const T &data) {
  if (p->left_) { return nullptr; }
  p->left_ = new BiNode<T>(data, p);
  ++size_;
  UpdateAbove(p);
  return p->left_;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::InsertAsRc(BNP p, const T &data) {
  if (p->right_) { return nullptr; }
  p->right_ = new BiNode<T>(data, p);
  ++size_;
  UpdateAbove(p);
  return p->right_;
}

template<typename T>
void BiTree<T>::UpdateHeight(BNP p) {
  SizeType left = p->left_ ? p->left_->height_ : -1;
  SizeType right = p->right_ ? p->right_->height_ : -1;
  p->height_ = left > right ? left : right;
}

template<typename T>
void BiTree<T>::UpdateAbove(BNP p) {
  while (p) {
    UpdateHeight(p);
    p = p->parent_;
  }
}

}  // namespace ds_cpp

#endif
