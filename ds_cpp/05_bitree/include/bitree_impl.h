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
BiTree<T>::~BiTree(){
  Remove(root_);
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Insert(const T &data) {
  if (root_) { return nullptr; }
  root_ = new BiNode<T>(data, nullptr);
  size_ = 1;
  return root_;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Insert(const T &data, BNP p) {
  auto left = p->InsertAsLc(data);
  if (left) {
    ++size_;
    UpdateHeightAbove(p);
  }
  return left;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Insert(BNP p, const T &data) {
  auto right = p->InsertAsRc(data);
  if (right) {
    ++size_;
    UpdateHeightAbove(p);
  }
  return right;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Attach(BiTree<T> &tree, BNP p) {
  if (p->left_ || !tree.root_) return nullptr;

  p->left_ = tree.root_;
  UpdateHeightAbove(p);
  size_ += tree.size_;
  tree.size_ = 0;
  tree.root_ = nullptr;
  p->left_->parent_ = p;

  return p->left_;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Attach(BNP p, BiTree<T> &tree) {
  if (p->right_ || !tree.root_) return nullptr;

  p->right_ = tree.root_;
  UpdateHeightAbove(p);
  size_ += tree.size_;
  tree.size_ = 0;
  tree.root_ = nullptr;
  p->right_->parent_ = p;

  return p->right_;
}

template<typename T>
typename BiTree<T>::SizeType BiTree<T>::Remove(BNP p) {
  if (!p) return 0;
  BiNode<T>::FromParentTo(p, root_) = nullptr;
  UpdateHeightAbove(p->parent_);
  SizeType num = RemoveAt(p);
  size_ -= num;
  return num;
}

template<typename T>
typename BiTree<T>::SizeType BiTree<T>::RemoveAt(BNP p) {
  if (!p) return 0;
  SizeType num = 1 + RemoveAt(p->lc_) + RemoveAt(p->rc_);
#if DEBUG
  std::cout << p->data_ << "\n";
#endif
  delete p;
  return num;
}

template<typename T>
BiTree<T> * BiTree<T>::Secede(BNP p) {
  if (!p) return nullptr;
  // 先组装
  auto tree = new BiTree<T>();
  tree->root_ = p;
  tree->size_ = p->Size();
  // 再分离
  size_ -= tree->size_;
  BiNode<T>::FromParentTo(p, root_) = nullptr;
  UpdateHeightAbove(p->parent_);
  p->parent_ = nullptr;

  return tree;
}

template<typename T>
void BiTree<T>::UpdateHeight(BNP p) {
  SizeType left = p->lc_ ? p->lc_->height_ : -1;
  SizeType right = p->rc_ ? p->rc_->height_ : -1;
  p->height_ = left > right ? left + 1: right + 1;
}

template<typename T>
void BiTree<T>::UpdateHeightAbove(BNP p) {
  while (p) {
    UpdateHeight(p);
    p = p->parent_;
  }
}

}  // namespace ds_cpp

#endif
