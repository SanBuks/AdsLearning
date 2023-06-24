template <typename T>
class BiTree {
 public:
  BiTree(const BiTree &rhs);
  BiTree(BiTree &&rhs) noexcept ;
  BiTree &operator=(const BiTree &rhs);
  BiTree &operator=(BiTree &&rhs) noexcept;


 protected:
  // 返回兄弟节点指针
  inline BNP Sibling(BNP p);
  // 返回叔叔节点指针
  inline BNP Uncle(BNP p);
 private:
  /*--------------------------- 功能函数 ------------------------------------*/
  // 拷贝子树初始化
  void CopyFrom(BNP p_source);
  // 从层次遍历序列初始化
  void CopyFrom(const Vector<T> &vec, const T &null);
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
inline typename BiTree<T>::BNP BiTree<T>::Sibling(BNP p) {
  return !p || IsRoot(p) ? nullptr :
         IsLc(p) ? p->parent_->rc_ : p->parent_->lc_;
}

template <typename T>
inline typename BiTree<T>::BNP BiTree<T>::Uncle(BNP p) {
  return !p || IsRoot(p) ? nullptr : Sibling(p->parent_);
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

