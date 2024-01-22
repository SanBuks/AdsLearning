export module ds_cpp.bst;
export import ds_cpp.bitree;

export namespace ds_cpp {

template <typename T>
class Bst : public BiTree<T> {

 public:
  using BNP = typename BiTree<T>::BNP;
  using SizeType = typename BiNode<T>::SizeType;

  Bst();
  Bst(const std::vector<T> &vec, const T &null);

  [[nodiscard]] BNP &SearchRef(const T &e);
  [[nodiscard]] virtual BNP Add(const T &e);
  [[nodiscard]] virtual bool Del(const T &e);
  [[nodiscard]] BNP DelAt(BNP &ref);

  [[nodiscard]] inline BNP pcache() const { return pcache_; }

 protected:
  BNP pcache_{};  // 父节点热缓存
};

template <typename T>
Bst<T>::Bst() = default;

template<typename T>
Bst<T>::Bst(const std::vector<T> &vec, const T &null) : BiTree<T>(vec, null) {}

template<typename T>
typename Bst<T>::BNP &Bst<T>::SearchRef(const T &e) {
  if (!this->root_ || this->root_->data() == e) {
    pcache_ = nullptr;
    return this->root_;
  }

  auto p = this->root_;
  while (p) {
    if (p->data() < e) {
      pcache_ = p;
      if (!p->rc()) {
        return p->Rc();
      }
      p = p->rc();
    } else if (e < p->data()) {
      pcache_ = p;
      if (!p->lc()) {
        return p->Lc();
      }
      p = p->lc();
    } else {
      return this->Ref(p, this->root_);
    }
  }
  return this->root_;
}

template<typename T>
typename Bst<T>::BNP Bst<T>::Add(const T &e) {
  auto &p = SearchRef(e);
  if (p) return p;
  p = new BiNode<T>(e, pcache_);
  this->UpdateHeightAbove(pcache_);
  ++this->size_;
  return p;
}

template<typename T>
bool Bst<T>::Del(const T &e) {
  auto &ref = SearchRef(e);
  if (!ref) return false;       // 没找到则返回 true
  auto pp = DelAt(ref);         // 更新 size, 返回实际删除节点的父亲节点
  --this->size_;                // 更新大小
  this->UpdateHeightAbove(pp);  // 更新高度
  return true;
}

template <typename T>
Bst<T>::BNP Bst<T>::DelAt(BNP &ref) {
  auto pp = pcache_;      // 父节点
  auto p = ref;           // 目标节点

  if (!p->lc()) {         // 单分支
    ref = p->rc();
    if (p->rc()) p->rc()->Parent() = pp;
    delete p;
  } else if(!p->rc()) {   // 单分支
    ref = p->lc();
    if (p->lc()) p->lc()->Parent() = pp;
    delete p;
  } else {                // 双分支
    auto successor = p->Successor();
    std::swap(p->Data(), successor->Data());
    pp = successor->parent();

    if (pp == p) {        // 右孩子正好是后继节点
      pp->Rc() = successor->rc();
    } else {             // 左藤树状态
      pp->Lc() = successor->rc();
    }

    if (successor->rc()) successor->rc()->Parent() = pp;
    delete successor;
  }
  return pp;
}

}