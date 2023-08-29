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
BiTree<T>::BiTree(const std::vector<T> &vec, const T &end) : size_(0), root_(nullptr) {
  if (vec.empty()) return;

  std::queue<BNP> queue;
  size_t index = 0;
  Insert(vec[index++]);
  queue.push(root_);

  while(index != vec.size()) {
     size_t num = queue.size();
     for (size_t i = 0; i != num; ++i) {
       BNP p = queue.front(); queue.pop();
       if (vec[index] != end) {
         auto left = Insert(vec[index], p);
         queue.push(left);
       }
       ++index;

       if (vec[index] != end) {
         auto right = Insert(p, vec[index]);
         queue.push(right);
       }
       ++index;
     }
  }
}

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
  FromParentTo(p) = nullptr;
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
  FromParentTo(p) = nullptr;
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

template <typename T>
template <typename VST>
void BiTree<T>::TraverseLevel(const VST &visit) {
  TraverseLevel(root_, visit);
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Zig(BNP p) {
  // 顺时针旋转, 旋转根节点没有左孩子则不旋转
  if (!BiNode<T>::HasLc(p)) { return p; }

  BNP lc = p->lc_;

  // 修改 左孩子的关系
  lc->parent_ = p->parent_;
  FromParentTo(p) = lc;

  // 修改 左孩子的右孩子的关系
  p->lc_ = lc->rc_;
  if (lc->rc_) lc->rc_->parent_ = p;

  // 修改 旋转节点和左孩子的关系
  lc->rc_ = p;
  p->parent_ = lc;

  // 先 更新 p 节点的高度
  p->height_ = 1 +
      (p->lc_ ? p->lc_->height_ : -1) +
      (p->rc_ ? p->rc_->height_ : -1);
  UpdateHeightAbove(lc);
  return lc;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Zag(BNP p) {
  // 逆时针旋转, 旋转根节点没有右孩子则不旋转
  if (!BiNode<T>::HasRc(p)) { return p; }

  BNP rc = p->rc_;

  // 修改 右孩子的关系
  rc->parent_ = p->parent_;
  FromParentTo(p) = rc;

  // 修改 右孩子的左孩子的关系
  p->rc_ = rc->lc_;
  if (rc->lc_) rc->lc_->parent_ = p;

  // 修改 旋转节点和右孩子的关系
  rc->lc_ = p;
  p->parent_ = rc;

  p->height_ = 1 +
      (p->lc_ ? p->lc_->height_ : -1) +
      (p->rc_ ? p->rc_->height_ : -1);

  UpdateHeightAbove(rc);
  return rc;
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
      p = p->lc_;
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
void BiTree<T>::TraverseInIteration(BNP p, const VST &visit) {
  if (!p) return;
  std::stack<BNP> stack;

  while (true) {
    if (p) {
      stack.push(p);
      p = p->lc_;
    } else if (!stack.empty()) {
      p = stack.top(); stack.pop();
      visit(p->data_);
      p = p->rc_;
    } else {
      break;
    }
  }
}

template<typename T>
template <typename VST>
void BiTree<T>::TraverseInIterationSuccession(BNP p, const VST &visit) {
  if (!p) return;
  bool backtrace = false;

  while (true) {
    if (!backtrace && BiNode<T>::HasLc(p)) {
      p = p->lc_;
    } else {
      visit(p->data_);
      if (BiNode<T>::HasRc(p)) {
        p = p->rc_;
        backtrace = false;
      } else {
        p = p->Succ();
        if (!p) break;
        backtrace = true;
      }
    }
  }
}


template<typename T>
template <typename VST>
void BiTree<T>::TraversePostIteration(BNP p, const VST &visit) {
  if (!p) return;
  std::stack<BNP> stack; stack.push(p);

  auto go_along_left_vine = [&stack]() {
    while (true) {
      auto p = stack.top();
      if (!p) break;

      if (BiNode<T>::HasLc(p)) {
        if (BiNode<T>::HasRc(p)) stack.push(p->rc_);
        stack.push(p->lc_);
      } else {
        stack.push(p->rc_);
      }
    }
    stack.pop();
  };

  while (!stack.empty()) {
    // 第一个访问的节点(叶子节点) 一定不是根节点的父节点, 一定优先访问
    // 访问后 p 指向上一个访问节点
    if (stack.top() != p->parent_) {
      go_along_left_vine();
    }
    p = stack.top();
    stack.pop();
    visit(p->data_);
  }
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseLevel(BNP p, const VST &visit) {
  std::queue<BNP> queue;
  queue.push(p);
  while (!queue.empty()) {
    SizeType size = queue.size();
    for (SizeType i = 0; i < size; ++i) {
      auto x = queue.front(); queue.pop();
      visit(x->data_);
      if (BiNode<T>::HasLc(x)) {
        queue.push(x->lc_);
      }
      if (BiNode<T>::HasRc(x)) {
        queue.push(x->rc_);
      }
    }
  }
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
