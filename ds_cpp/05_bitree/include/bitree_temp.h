template <typename T>
class BiTree {
 public:
  using HeightType = typename BiNode<T>::HeightType;

  /*---------------------------- 拷贝控制 -----------------------------------*/
  BiTree(const Vector<T> &vec, const T &null);  // null 表示空节点
  BiTree(const BiTree &rhs);
  BiTree(BiTree &&rhs) noexcept ;
  BiTree &operator=(const BiTree &rhs);
  BiTree &operator=(BiTree &&rhs) noexcept;
  ~BiTree();

  /*--------------------------- 只读访问 ------------------------------------*/

  // 获取子树节点个数
  Size GetSubTreeSize(BNP p) const;

  // 三种遍历 递归
  template <typename VST> void TraversePreOrderR(BNP p, const VST &visit) const;
  template <typename VST> void TraversePreOrderR(const VST &visit) const;
  template <typename VST> void TraversePostOrderR(BNP p, const VST &visit) const;
  template <typename VST> void TraversePostOrderR(const VST &visit) const;
  template <typename VST> void TraverseInOrderR(BNP p, const VST &visit) const;
  template <typename VST> void TraverseInOrderR(const VST &visit) const;

  // 先序遍历 迭代
  template <typename VST> void TraversePreOrderI1(BNP p, const VST &visit) const;
  template <typename VST> void TraversePreOrderI1(const VST &visit) const;
  template <typename VST> void TraversePreOrderI2(BNP p, const VST &visit) const;
  template <typename VST> void TraversePreOrderI2(const VST &visit) const;
  // 中序遍历 迭代
  template <typename VST> void TraverseInOrderI1(BNP p, const VST &visit) const;
  template <typename VST> void TraverseInOrderI1(const VST &visit) const;
  template <typename VST> void TraverseInOrderI2(BNP p, const VST &visit) const;
  template <typename VST> void TraverseInOrderI2(const VST &visit) const;
  template <typename VST> void TraverseInOrderI3(BNP p, const VST &visit) const;
  template <typename VST> void TraverseInOrderI3(const VST &visit) const;
  // 后序遍历 迭代
  // 层次遍历
  template <typename VST> void TraverseLevel(BNP p, const VST &visit) const;
  template <typename VST> void TraverseLevel(const VST &visit) const;

  /*--------------------------- 可写访问 ------------------------------------*/
  // 节点插入作为根
  BNP InsertAsRoot(const T &elem);
  // 节点插入作为左孩子
  BNP InsertAsLc(BNP p, const T &elem);
  // 节点插入作为右孩子
  BNP InsertAsRc(BNP p, const T &elem);

  // 二叉树作为左子树接入
  BNP AttachAsLc(BNP p, BiTree &tree);
  // 二叉树作为右子树接入
  BNP AttachAsRc(BNP p, BiTree &tree);

  // 删除子树, 返回删除节点个数
  Size Remove(BNP p);
  // 摘离子树 如果出错返回 nullptr
  BiTree *Secede(BNP p);

 protected:
  /*----------------------------- 更新节点信息 --------------------------------*/
  // 更新 p 所指节点的高度 因树而异
  virtual void UpdateHeight(BNP p);
  // 更新 p 所指节点的祖先高度
  void UpdateHeightAbove(BNP p);

  /*----------------------------- 获取节点信息 --------------------------------*/
  // 返回 节点指针的高度, 如果空指针则为返回 -1
  inline HeightType Stature(BNP p) const;

  // 返回兄弟节点指针
  inline BNP Sibling(BNP p);
  // 返回叔叔节点指针
  inline BNP Uncle(BNP p);
  // 返回父节点指向 p 所指节点的指针引用
  inline BNP &FromParentTo(BNP p);

  /*--------------------------- 数据成员 ------------------------------------*/
  Size size_; // 节点个数
  BNP root_;  // 树根

 private:
  /*--------------------------- 功能函数 ------------------------------------*/
  // 拷贝子树初始化
  void CopyFrom(BNP p_source);
  // 从层次遍历序列初始化
  void CopyFrom(const Vector<T> &vec, const T &null);

  template <typename VST>
  void VisitAlongLeftBranch(BNP p, Stack<BNP> &stack, const VST &visit) const ;
};


template <typename T>
BiTree<T>::BiTree(const Vector<T> &vec, const T &null)
    : size_(0), root_(nullptr) {
  CopyFrom(vec, null);
}

template <typename T>
BiTree<T>::BiTree(const BiTree &rhs) : size_(0), root_(nullptr) {
  CopyFrom(rhs.root_);
}

template <typename T>
BiTree<T>::BiTree(BiTree &&rhs) noexcept
    : size_(rhs.size_), root_(rhs.root_) {
  rhs.size_ = 0;
  rhs.root_ = nullptr;
}

template <typename T>
BiTree<T> &BiTree<T>::operator=(const BiTree &rhs) {
  using std::swap;
  if (this != &rhs) {
    BiTree temp(rhs);
    swap(*this, temp);
  }
  return *this;
}

template <typename T>
BiTree<T> &BiTree<T>::operator=(BiTree &&rhs) noexcept {
  if (&rhs != this) {
    Remove(root_);

    root_ = rhs.root_;
    size_ = rhs.size_;

    rhs.size_ = 0;
    rhs.root_ = nullptr;
  }
  return *this;
}

template <typename T>
BiTree<T>::~BiTree() {
  Remove(root_);
}

template <typename T>
typename BiTree<T>::Size BiTree<T>::GetSubTreeSize(BNP p) const {
  if (!p) {
    return 0;
  }

  Size num = 0;
  Queue<BNP> queue;
  queue.Enqueue(p);
  while (!queue.Empty()) {
    auto temp = queue.Dequeue();
    ++num;
    if (HasLc(temp)) {
      queue.Enqueue(temp->lc_);
    }
    if (HasRc(temp)) {
      queue.Enqueue(temp->rc_);
    }
  }
  return num;
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePreOrderR(BNP p, const VST &visit) const {
  if (!p) {
    return;
  }
  visit(p->data_);
  TraversePreOrderR(p->lc_, visit);
  TraversePreOrderR(p->rc_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePreOrderR(const VST &visit) const {
  TraversePreOrderR(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePostOrderR(BNP p, const VST &visit) const {
  if (!p) {
    return;
  }
  TraversePostOrderR(p->lc_, visit);
  TraversePostOrderR(p->rc_, visit);
  visit(p->data_);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePostOrderR(const VST &visit) const {
  TraversePostOrderR(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInOrderR(BNP p, const VST &visit) const {
  if (!p) {
    return;
  }
  TraverseInOrderR(p->lc_, visit);
  visit(p->data_);
  TraverseInOrderR(p->rc_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInOrderR(const VST &visit) const {
  TraverseInOrderR(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePreOrderI1(BNP p, const VST &visit) const {
  if (!p) {
    return;
  }

  Stack<BNP> stack;
  stack.Push(p);
  while (!stack.Empty()) {
    auto tp = stack.Pop();
    visit(tp->data_);
    if (tp->rc_) {
      stack.Push(tp->rc_);
    }
    if (tp->lc_) {
      stack.Push(tp->lc_);
    }
  }
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePreOrderI1(const VST &visit) const {
  TraversePreOrderI1(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePreOrderI2(BNP p, const VST &visit) const {
  if (!p) {
    return;
  }
  Stack<BNP> stack;
  stack.Push(p);
  while (!stack.Empty()) {
    auto tp = stack.Pop();
    VisitAlongLeftBranch(tp, stack, visit);
  }
}

template <typename T>
template <typename VST>
void BiTree<T>::TraversePreOrderI2(const VST &visit) const {
  TraversePreOrderI2(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInOrderI1(BNP p, const VST &visit) const {

}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInOrderI1(const VST &visit) const {
  TraverseInOrderI1(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInOrderI2(BNP p, const VST &visit) const {

}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInOrderI2(const VST &visit) const {
  TraverseInOrderI2(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInOrderI3(BNP p, const VST &visit) const {

}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseInOrderI3(const VST &visit) const {
  TraverseInOrderI3(root_, visit);
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseLevel(BNP p, const VST &visit) const {
  if (!p) {
    return;
  }

  Queue<BNP> queue;
  queue.Enqueue(p);
  while (!queue.Empty()) {
    auto tp = queue.Dequeue();
    visit(tp->data_);
    if (tp->lc_) {
      queue.Enqueue(tp->lc_);
    }
    if (tp->rc_) {
      queue.Enqueue(tp->rc_);
    }
  }
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseLevel(const VST &visit) const {
  TraverseLevel(root_, visit);
}

template <typename T>
typename BiTree<T>::BNP BiTree<T>::InsertAsRoot(const T &elem) {
  if (!root_) {
    size_ = 1;
    return root_ = new BiNode<T>(elem);
  } else {
    return nullptr;
  }
}

template <typename T>
typename BiTree<T>::BNP BiTree<T>::InsertAsLc(BNP p, const T &elem) {
  if (!p) {
    return nullptr;
  }

  BNP p_insert = p->InsertAsLc(elem);
  if (p_insert) {
    UpdateHeightAbove(p_insert);
    ++size_;
  }
  return p_insert;
}

template <typename T>
typename BiTree<T>::BNP BiTree<T>::InsertAsRc(BNP p, const T &elem) {
  if (!p) {
    return nullptr;
  }

  BNP p_insert = p->InsertAsRc(elem);
  if (p_insert) {
    UpdateHeightAbove(p_insert);
    ++size_;
  }
  return p_insert;
}

template <typename T>
typename BiTree<T>::BNP BiTree<T>::AttachAsLc(BNP p, BiTree &tree) {
  if (!p || p->lc_) {
    return nullptr;
  }

  // 接入
  p->lc_ = tree.root_;
  if (p->lc_) {
    p->lc_->parent_ = p;
  }
  // 更新
  size_ += tree.size_;
  UpdateHeightAbove(p);
  // 处理为空树
  tree.root_ = nullptr;
  tree.size_ = 0;

  return p;
}

template <typename T>
typename BiTree<T>::BNP BiTree<T>::AttachAsRc(BNP p, BiTree &tree) {
  if (!p || p->rc_) {
    return nullptr;
  }

  // 接入
  p->rc_ = tree.root_;
  if (p->rc_) {
    p->rc_->parent_ = p;
  }
  // 更新
  size_ += tree.size_;
  UpdateHeightAbove(p);
  // 处理为空树
  tree.root_ = nullptr;
  tree.size_ = 0;

  return p;
}

template <typename T>
typename BiTree<T>::Size BiTree<T>::Remove(BNP p) {
  if (!p) {
    return 0;
  }

  // 分离并更新高度
  FromParentTo(p) = nullptr;
  UpdateHeightAbove(p->parent_);

  // 层次遍历删除节点
  Size num_remove = 0;
  Queue<BNP> queue;
  queue.Enqueue(p);
  while (!queue.Empty()) {
    auto p_temp = queue.Dequeue();
    if (p_temp->lc_) {
      queue.Enqueue(p_temp->lc_);
    }
    if (p_temp->rc_) {
      queue.Enqueue(p_temp->rc_);
    }
    delete p_temp;
    ++num_remove;
  }

  // 更新个数
  size_ -= num_remove;

  return num_remove;
}

template <typename T>
BiTree<T> *BiTree<T>::Secede(BNP p) {
  if (!p) {
    return nullptr;
  }

  auto *p_subtree = new BiTree<T>();

  Size subtree_size = GetSubTreeSize(p);
  FromParentTo(p) = nullptr;
  UpdateHeightAbove(p->parent_);
  size_ -= subtree_size;

  p->parent_ = nullptr;
  p_subtree->size_ = subtree_size;
  p_subtree->root_ = p;

  return p_subtree;
}

template <typename T>
void BiTree<T>::UpdateHeight(BNP p) {
  auto lh = Stature(p->lc_);
  auto rh = Stature(p->rc_);
  p->height_ = 1 + (lh < rh ? rh : lh);
}

// 更新 p 所指节点祖先的高度
template <typename T>
void BiTree<T>::UpdateHeightAbove(BNP p) {
  while (p) {
    UpdateHeight(p);
    p = p->parent_;
  }
}

template <typename T>
inline typename BiTree<T>::HeightType BiTree<T>::Stature(BNP p) const {
  return p ? p->height_ : -1;
}

template <typename T>
inline typename BiTree<T>::BNP BiTree<T>::Sibling(BNP p) {
  return !p || IsRoot(p) ? nullptr :
         IsLc(p) ? p->parent_->rc_ : p->parent_->lc_;
}

template <typename T>
inline typename BiTree<T>::BNP BiTree<T>::Uncle(BNP p) {
  return !p || IsRoot(p) ? nullptr : Sibling(p->parent_);
}

template <typename T>
inline typename BiTree<T>::BNP &BiTree<T>::FromParentTo(BNP p) {
  return IsRoot(p) ? root_ : IsLc(p) ? p->parent_->lc_: p->parent_->rc_;
}

template <typename T>
void BiTree<T>::CopyFrom(BNP p_source) {
  if (!p_source) {
    return;
  }

  root_ = new BiNode<T>(p_source->data_);
  size_ = 1;

  Queue<BNP> target_queue;
  Queue<BNP> source_queue;

  target_queue.Enqueue(root_);
  source_queue.Enqueue(p_source);

  while (!source_queue.Empty()) {
    auto pt_target = target_queue.Dequeue();
    auto pt_source = source_queue.Dequeue();
    if (pt_source->lc_) {
      target_queue.Enqueue(InsertAsLc(pt_target, pt_source->lc_->data_));
      source_queue.Enqueue(pt_source->lc_);
    }
    if (pt_source->rc_) {
      target_queue.Enqueue(InsertAsRc(pt_target, pt_source->rc_->data_));
      source_queue.Enqueue(pt_source->rc_);
    }
  }
}

template <typename T>
void BiTree<T>::CopyFrom(const Vector<T> &vec, const T &null) {
  if (vec.Empty() || vec[0] == null) {
    return;
  }

  root_ = new BiNode<T>(vec[0]);
  size_ = 1;

  Queue<BNP> queue;
  queue.Enqueue(root_);
  typename Vector<T>::Rank i = 1;
  auto size = vec.size();

  while (!queue.Empty() && i < size) {
    auto p = queue.Dequeue();
    if (vec[i] != null) {
      auto temp_p = InsertAsLc(p, vec[i]);
      queue.Enqueue(temp_p);
    }
    if (++i >= size) {
      // 如果没有遍历所有孩子则重新进入队列, 表示错误
      queue.Enqueue(p);
      break;
    }
    if (vec[i] != null) {
      auto temp_p = InsertAsRc(p, vec[i]);
      queue.Enqueue(temp_p);
    }
    ++i;
  }

  if (i != size || !queue.Empty()) {
    Remove(root_);
    throw std::runtime_error(bitree_error::kConstructFromVectorError);
  }
}

template <typename T>
template <typename VST>
void BiTree<T>::VisitAlongLeftBranch(BNP p, Stack<BNP> &stack,
                                     const VST &visit) const {
  while (p) {
    visit(p->data_);
    if (p->rc_) {
      stack.Push(p->rc_);
    }
    p = p->lc_;
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

