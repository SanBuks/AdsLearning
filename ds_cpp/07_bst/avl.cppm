export module ds_cpp.avl;
export import ds_cpp.bitree;

import ds_cpp.bst;

export namespace ds_cpp {

template <typename T>
class Avl : public Bst<T> {
 public:
  using BNP = typename BiNode<T>::BNP;
  using SizeType = typename BiNode<T>::SizeType;

  static constexpr int kFactor = 2;

  Avl();
  Avl(const std::vector<T> &vec, const T &null);

  // 平衡因子
  [[nodiscard]] inline static SizeType BalancedFactor(BNP p) {
    SizeType lh = p->lc() ? p->lc()->height() + 1 : 0;
    SizeType rh = p->rc() ? p->rc()->height() + 1 : 0;
    return lh > rh ? lh - rh : rh - lh;
  }
  // 理想平衡
  [[nodiscard]] inline static bool Balanced(BNP p) { return BalancedFactor(p) == 0;  }
  // AVL 平衡
  [[nodiscard]] inline static bool AvlBalanced(BNP p) { return BalancedFactor(p) < kFactor; }

  [[nodiscard]] BNP Add(const T &e) override;
  [[nodiscard]] bool Del(const T &e) override;
 private:
  // 返回较高孩子节点, 如果高度相同则与 p 同侧优先
  BNP TallerChild(BNP p);
  // 统一旋转
  BNP Rotate(BNP p);
  BNP Connect34(BNP left, BNP parent, BNP right, BNP ll, BNP lr, BNP rl, BNP rr);
};

template <typename T>
Avl<T>::Avl() = default;

template<typename T>
Avl<T>::Avl(const std::vector<T> &vec, const T &null) : Bst<T>(vec, null) {}

template<typename T>
Avl<T>::BNP Avl<T>::Add(const T &e) {
  auto &ref = this->SearchRef(e);
  if (ref) return ref;
  ref = new BiNode<T>(e, this->pcache_);
  ++this->size_;
  auto pos = ref;

  // 从插入的父亲节点朝上遍历
  for (auto g = this->pcache_; g; g = g->parent()) {
    if (!AvlBalanced(g)) {
      // 存在不平衡则旋转
      auto &refg = this->Ref(g, this->root_);  // 提前保存指向 g 的引用
      auto v = TallerChild(g);
      auto p = TallerChild(v);
      refg = Rotate(p);
      break;
    } else {
      // 虽然平衡高度仍需要更新
      this->UpdateHeight(g);
    }
  }
  // 返回插入节点的位置 (更新后)
  return pos;
}

template<typename T>
Avl<T>::BNP Avl<T>::TallerChild(BNP p) {
  if (!p) return p;

  SizeType lc = p->lc() ? p->lc()->height() + 1 : 0;
  SizeType rc = p->rc() ? p->rc()->height() + 1 : 0;

  if (lc < rc) return p->rc();
  if (rc < lc) return p->lc();

  if (BiNode<T>::HasParent(p)) {
    return BiNode<T>::IsLc(p) ? p->lc() : p->rc();
  }
  return p->lc();
}

template<typename T>
bool Avl<T>::Del(const T &e) {

  return false;
}

//              RR单旋                          RL双旋
//        g                 v            g                p
//      1   v     ->      g   p        1   v   ->       g   v
//        2   p          1 2 3 4         p   2         1 3 4 2
//          3   4                       3 4
//              LL单旋                          RL双旋
//           g              v             g                p
//         v   1  ->      p   g         v   1   ->       v   g
//       p   2           4 3 2 1       2  p             2 3 4 1
//    4   3                              3 4
template<typename T>
Avl<T>::BNP Avl<T>::Rotate(Avl::BNP p) {
  BNP v = p->parent();
  BNP g = v->parent();
  auto pp = g->parent();

  // 注意 类型 和 判断顺序 相反
  if (BiNode<T>::IsRc(p)) {
    if (BiNode<T>::IsRc(g)) {  // RR
      v->Parent() = pp;
      return Connect34(g, v, p, g->lc(), v->lc(), p->lc(), p->rc());
    } else {                   // LR
      p->Parent() = pp;
      return Connect34(v, p, g, v->lc(), p->lc(), p->rc(), g->rc());
    }
  } else {
    if (BiNode<T>::IsLc(g)) {  // LL
      v->Parent() = pp;
      return Connect34(p, v, g, p->lc(), p->rc(), v->rc(), g->rc());
    } else {                   // RL
      p->Parent() = pp;
      return Connect34(g, p, v, g->lc(), p->lc(), p->rc(), v->rc());
    }
  }
}

template<typename T>
Avl<T>::BNP Avl<T>::Connect34(BiNode<T>::BNP left, BiNode<T>::BNP parent, BiNode<T>::BNP right,
                              BiNode<T>::BNP ll, BiNode<T>::BNP lr, BiNode<T>::BNP rl, BiNode<T>::BNP rr) {
  // 处理 "4" 个关系
  left->Lc() = ll; if (ll) ll->Parent() = left;
  left->Rc() = lr; if (lr) lr->Parent() = left;
  right->Lc() = rl; if (rl) rl->Parent() = right;
  right->Rc() = rr; if (rr) rr->Parent() = right;

  // 处理 "3" 个节点
  parent->Lc() = left; left->Parent() = parent;
  parent->Rc() = right; right->Parent() = parent;

  // 更新高度
  this->UpdateHeight(left);
  this->UpdateHeight(right);
  this->UpdateHeight(parent);
  return parent;
}

}