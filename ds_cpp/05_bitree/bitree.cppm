export module ds_cpp.bitree;
export import :binode;
export import :common;

import <vector>;
import <deque>;
import <ostream>;
import <stack>;

export namespace ds_cpp {

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
  [[nodiscard]] std::ostream& io() const { return io_; }
 private:
  std::ostream& io_;
};

template <typename T> class BiTree;
template<typename T> void swap(BiTree<T> &lhs, BiTree<T> &rhs) noexcept;

// 二叉树模板类 (含父节点)
template <typename T>
class BiTree {

 public:
  using SizeType = BiTreeType::SizeType;
  using BNP = typename BiNode<T>::BNP;

  BiTree() = default;
  BiTree(const std::vector<T> &vec, const T &null);  // 层次遍历构造二叉树
  BiTree(const BiTree &rhs) = delete;
  BiTree(BiTree &&rhs) = delete;
  BiTree& operator=(const BiTree &rhs) = delete;
  BiTree& operator=(BiTree &&rhs) = delete;
  ~BiTree();

  [[nodiscard]] BNP root() const { return root_; }
  [[nodiscard]] SizeType size() const { return size_; }
  [[nodiscard]] bool empty() const { return !size_; }

  static SizeType RemoveAt(BNP p);    // 递归删除子树所有节点, 返回删除节点个数
  static BNP &Ref(BNP p, BNP &root);  // 返回父节点对 p 的引用, 如果是根节点则返回 root 引用

  BNP Insert(const T &data);          // 插入根
  BNP Insert(const T &data, BNP p);   // 插入左孩子, 更新高度
  BNP Insert(BNP p, const T &data);   // 插入右孩子, 更新高度
  SizeType Remove(BNP p);             // 删除子树

  BNP Attach(BiTree<T> &tree, BNP p); // 接入左子树
  BNP Attach(BNP p, BiTree<T> &tree); // 接入左子树
  BiTree *Secede(BNP p);              // 分离子树
  BNP Zig(BNP p);                     // 顺时针右旋, p 所指节点变为左孩子的左节点, 左孩子变为 p 所指节点的父节点
  BNP Zag(BNP p);                     // 逆时针左旋, p 所指节点变为右孩子的右节点, 右孩子变为 p 所指节点的父节点

  template <typename VST> void TraverseLevel(const VST &visit);        // 层次遍历
  template <typename VST> void TraversePre(const VST &visit);          // 先序迭代遍历
  template <typename VST> void TraverseIn(const VST &visit);           // 中序迭代遍历
  template <typename VST> void TraverseInBacktrace(const VST &visit);  // 中序迭代遍历回溯法
  template <typename VST> void TraversePost(const VST &visit);         // 后序迭代遍历

 protected:
  void UpdateHeightAbove(BNP p);      // 更新节点及祖先节点高度
  void UpdateHeight(BNP p);           // 更新节点高度

  BNP root_{};       // 指向根节点
  SizeType size_{};  // 结点个数

 private:
  void BuildFromLevel(const std::vector<T> &vec, const T &null); // 层次遍历构建二叉树
};

template<typename T>
void swap(BiTree<T> &lhs, BiTree<T> &rhs) noexcept {
  using std::swap;
  swap(lhs.root_, rhs.root_);
  swap(lhs.size_, rhs.size_);
}

template<typename T>
BiTree<T>::~BiTree() {
  Remove(root_);
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Insert(const T &data) {
  if (root_) { return nullptr; }
  root_ = new BiNode<T>(data);
  size_ = 1;
  return root_;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Insert(const T &data, BNP p) {
  auto q = p->InsertAsLc(data);
  if (q) {
    UpdateHeightAbove(p);
    ++size_;
  }
  return q;
}

template<typename T>
BiTree<T>::SizeType BiTree<T>::RemoveAt(BNP p) {
  if (!p) return 0;
  auto num = 1 + RemoveAt(p->lc_) + RemoveAt(p->rc_);
  delete p;
  return num;
}

template<typename T>
typename BiTree<T>::BNP & BiTree<T>::Ref(BNP p, BNP &root) {
  if (BiNode<T>::HasParent(p)) {
    return BiNode<T>::IsLc(p) ? p->parent_->lc_ : p->parent_->rc_;
  } else {
    return root;
  }
}

template<typename T>
BiTree<T>::SizeType BiTree<T>::Remove(BNP p) {
  if (!p) return 0;

  auto parent = p->parent_;
  Ref(p, root_) = nullptr;
  auto remove_size = RemoveAt(p);
  size_ -= remove_size;
  UpdateHeightAbove(parent);
  return remove_size;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Insert(BNP p, const T &data) {
  auto q = p->InsertAsRc(data);
  if (q) {
    UpdateHeightAbove(p);
    ++size_;
  }
  return q;
}

template <typename T>
template <typename VST>
void BiTree<T>::TraverseLevel(const VST &visit) {
  if (!root_) return;
  std::deque<BNP> queue;
  queue.push_back(root_);
  while (!queue.empty()) {
    auto size = queue.size();
    for (std::size_t i = 0; i != size; ++i) {
      auto p = queue.front(); queue.pop_front();
      visit(p->data());
      if (p->lc_) queue.push_back(p->lc_);
      if (p->rc_) queue.push_back(p->rc_);
    }
  }
}

template <typename T>
template<typename VST>
void BiTree<T>::TraversePre(const VST &visit) {
  if (!root_) return ;
  std::stack<BNP> stack;
  auto visit_along_left = [&stack, &visit](BNP p) {
    while (p) {
      visit(p->data_);
      if (p->rc_) stack.push(p->rc_);
      p = p->lc_;
    }
  };

  visit_along_left(root_);
  while (!stack.empty()) {
    auto p = stack.top(); stack.pop();
    visit_along_left(p);
  }
}

template <typename T>
template<typename VST>
void BiTree<T>::TraverseIn(const VST &visit) {
  if (!root_) return;
  std::stack<BNP> stack;

  auto go_along_left = [&stack](BNP p) {
    while (p) {
      stack.push(p);
      p = p->lc_;
    }
  };

  go_along_left(root_);
  while (!stack.empty()) {
    auto p = stack.top(); stack.pop();
    visit(p->data_);
    if (p->rc_)
      go_along_left(p->rc_);
  }
}

template <typename T>
template<typename VST>
void BiTree<T>::TraverseInBacktrace(const VST &visit) {
  if (!root_) return;

  bool backtrace = false;
  auto p = root_;

  while (true) {
    if (!p) break;
    if (!backtrace && p->lc_) {
      p = p->lc_;
    } else {
      visit(p->data_);
      if (!p->rc_) {
        backtrace = true;
        p->Successor();
      } else {
        backtrace = false;
        p = p->rc_;
      }
    }
  }
}

template <typename T>
template<typename VST>
void BiTree<T>::TraversePost(const VST &visit) {
  if (!root_) return;
  std::stack<BNP> stack;
  auto go_along_left = [&stack](BNP p) {
    while (p) {
      stack.push(p);
      if (p->rc_) stack.push(p->rc_);
      p = p->lc_;
    }
  };
  go_along_left(root_);
  BNP last = nullptr;
  while (!stack.empty()) {
    auto p = stack.top(); stack.pop();
    bool trace_back = last && (last == p->lc_ || last == p->rc_);
    if (!stack.empty() && BiNode<T>::HasC(p) && !trace_back) {
      go_along_left(p);
    } else {
      visit(p->data_);
      last = p;
    }
  }
}

template<typename T>
BiTree<T>::BiTree(const std::vector<T> &vec, const T &null) {
  if (vec.empty()) return;
  BuildFromLevel(vec, null);
}

template<typename T>
void BiTree<T>::BuildFromLevel(const std::vector<T> &vec, const T &null) {
  // 插入根节点, 失败则直接退出
  auto r = Insert(vec[0]);
  if (!r) return;

  // vec 下一个元素位置
  std::size_t pos = 1;

  // 层次遍历
  std::deque<BNP> queue;
  queue.push_back(r);
  while (!queue.empty()) {
    auto size = queue.size();

    for (std::size_t i = 0; i != size; ++i) {
      auto p = queue.front(); queue.pop_front();

      // 如果 vec 元素数量不够, 直接完成构建
      if (pos == vec.size()) return;
      if (vec[pos] != null) {
        auto q = Insert(vec[pos], p);
        queue.push_back(q);
      }
      ++pos;

      if (pos == vec.size()) return;
      if (vec[pos] != null) {
        auto q = Insert(p, vec[pos]);
        queue.push_back(q);
      }
      ++pos;
    }
  }
}

template<typename T>
void BiTree<T>::UpdateHeightAbove(BNP p) {
  while (p) {
    UpdateHeight(p);
    p = p->parent_;
  }
}

template<typename T>
void BiTree<T>::UpdateHeight(BNP p) {
  if (!p) return;
  auto lh = p->lc_ ? p->lc_->height_ : 0;
  auto rh = p->rc_ ? p->rc_->height_ : 0;
  p->height_ = 1 + (lh < rh ? rh : lh);
  // 如果没有 lc 和 rc 则修正为 0 而非 1
  p->height_ = BiNode<T>::HasC(p) ? p->height_ : 0;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Attach(BiTree<T> &tree, BNP p) {
  if (!p) return p;
  if (p->lc_) return p->lc_;

  auto r = tree.root();
  p->lc_ = r;
  r->parent_ = p;
  UpdateHeightAbove(p);
  size_ += tree.size();

  tree.root_ = nullptr;
  tree.size_ = 0;

  return p->lc_;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Attach(BNP p, BiTree<T> &tree) {
  if (!p) return p;
  if (p->rc_) return p->rc_;

  auto r = tree.root();
  p->rc_ = r;
  r->parent_ = p;
  UpdateHeightAbove(p);
  size_ += tree.size();

  tree.root_ = nullptr;
  tree.size_ = 0;

  return p->rc_;
}

template<typename T>
BiTree<T> *BiTree<T>::Secede(BNP p) {
  auto tree = new BiTree;

  auto size = p->Size();
  tree->size_ = size;
  size_ -= size;

  auto parent = p->parent_;
  Ref(p, root_) = nullptr;
  UpdateHeightAbove(parent);

  tree->root_ = p;
  p->parent_ = nullptr;

  return tree;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Zig(BNP p) {
  //     r                  a
  //  a     b      ->     c   r
  // c d   e f              d   b
  //                           e f

  if (!p || !p->lc_) return p;

  auto left = p->lc_;
  auto parent = p->parent_;

  // 改变根关系
  left->parent_ = parent;
  Ref(p, root_) = left;

  // 改变子树嫁接关系
  p->lc_ = left->rc_;
  if (left->rc_) left->rc_->parent_ = p;

  // 改变旋转关系
  p->parent_ = left;
  left->rc_ = p;
  UpdateHeightAbove(p);

  return left;
}

template<typename T>
typename BiTree<T>::BNP BiTree<T>::Zag(BNP p) {
  //     r                  b
  //  a     b      ->     r   f
  // c d   e f          a  e
  //                  c  d
  if (!p || !p->rc_) return p;

  auto right = p->rc_;
  auto parent = p->parent_;

  right->parent_ = parent;
  Ref(p, root_) = right;

  p->rc_ = right->lc_;
  if (right->lc_) right->lc_->parent_ = p;

  p->parent_ = right;
  right->lc_ = p;

  UpdateHeightAbove(p);
  return right;
}

}