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
  if (p->left() || !tree.root_) return nullptr;

  p->left_ = tree.root_;
  p->left_->parent_ = p;
  UpdateHeightAbove(p);
  tree.root_ = nullptr;

  size_ += tree.size_;
  tree.size_ = 0;

  return p->left_;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Attach(BNP p, BiTree<T> &tree) {
  if (p->right_ || !tree.root_) return nullptr;

  p->right_ = tree.root_;
  p->right_->parent_ = p;
  UpdateHeightAbove(p);
  tree.root_ = nullptr;

  size_ += tree.size_;
  tree.size_ = 0;

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

template <typename T>
template <typename VST>
void BiTree<T>::TraversePreIteration(const VST &visit) {
  TraversePreIteration(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInIterationVine(const VST &visit) {
  TraverseInIterationVine(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInIterationSuccession(const VST &visit) {
  TraverseInIterationSuccession(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInIteration(const VST &visit) {
  TraverseInIteration(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePostIteration(const VST &visit) {
  TraversePostIteration(root_, visit);
}

template<typename T>
void BiTree<T>::UpdateHeight(BNP p) {
  //  获取子树高度后 + 1, 空树高度为零
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

template <typename T>
template <typename VST>
void BiTree<T>::TraversePreIteration(BNP p, const VST &visit) {
  if (!p) return;

  std::stack<BNP> stack; stack.push(p);
  while (!stack.empty()) {
    p = stack.top();
    stack.pop();
    // 遍历 左藤
    while (p) {
      visit(p->data_);
      if (p->rc_) stack.push(p->rc_);
      p = p->rc_;
    }
  }
}

template<typename T>
template <typename VST>
void BiTree<T>::TraverseInIterationVine(BNP p, const VST &visit) {
  if (!p) return;

  std::stack<BNP> stack;
  auto go_along_left_vine = [&stack](BNP p) {
    while (p) { stack.push(p); p = p->lc_; }
  };
  go_along_left_vine(p);
  while (!stack.empty()) {
    p = stack.top();
    stack.pop();
    visit(p->data_);
    p = p->rc_;
    if (p) go_along_left_vine(p);
  }
}

template<typename T>
template <typename VST>
void BiTree<T>::TraverseInIterationSuccession(BNP p, const VST &visit) {

}

template<typename T>
template <typename VST>
void BiTree<T>::TraverseInIteration(BNP p, const VST &visit) {

}

template<typename T>
template <typename VST>
void BiTree<T>::TraversePostIteration(BNP p, const VST &visit) {

}

// 遍历调用对象类型
template <typename T>
class BiTreeTraverse {
 public:
  explicit BiTreeTraverse(std::ostream &io) : io_(io) {}
  void operator()(const T &e) const {
    io_ << e << " ";
  }
  void operator()(T &e) const {
    io_ << e << " ";
  }
  std::ostream& io() const { return io_; }
 private:
  std::ostream& io_;
};

}  // namespace ds_cpp

#endif
