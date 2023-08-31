#include <iostream>
#include <utility>
using namespace std;

struct Node {
  int value;  // 数值
  int height; // 高度
  int lnum;   // 左子树节点个数
  int rnum;   // 右子树节点个数
  int num;    // 当前节点重复个数
  Node *pa;   // 父指针
  Node *lc;   // 左孩子指针
  Node *rc;   // 右孩子指针

  explicit Node(int val, Node *p = nullptr, Node *l = nullptr, Node *r = nullptr) {
    value = val;
    height = 1 + max(Stature(l), Stature(r));
    num = 1;
    lnum = l ? l->Num() : 0;
    rnum = r ? r->Num() : 0;
    pa = p;
    lc = l;
    rc = r;
  }

  inline int Num() const {
    return lnum + rnum + num;
  }

  inline static int Stature(Node *p) {
    return p ? p->height : -1;
  }
};

class AvlTree {
 public:
  explicit AvlTree() : root(nullptr) {}

  Node *add(int value) {
    auto result = search(value);
    Node * &target = result.first;
    Node * ptarget = result.second;

    // 找到直接增加计数, 更新祖先节点的子树个数
    if (target) {
      ++target->num;
      UpdateNumAbove(target);
      return target;
    }

    // 没找到则增加节点
    target = new Node(value, ptarget);
    Node *ans = target;
    Node *g = ans;
    for (; g; g = g->pa) {
      if (!Balanced(g)) {
        Node *v = TallerChild(TallerChild(g));
        Node * &ref = FromParentTo(g);
        Node *subTree = Rotate(v);
        ref = subTree;
        break;
      } else {
        UpdateHeight(g);
        UpdateNum(g);
      }
    }

    UpdateNumAbove(g);
    return ans;
  }

  inline static Node *TallerChild(Node *p) {
    int lheight = Node::Stature(p->lc);
    int rheight = Node::Stature(p->rc);
    if (lheight > rheight) {
      return p->lc;
    } else if (lheight < rheight) {
      return p->rc;
    } else {
      return IsLc(p) ? p->lc : p->rc;
    }
  }

  static void UpdateHeightAbove(Node *p) {
    while (p) {
      UpdateHeight(p);
      p = p->pa;
    }
  }

  static void UpdateHeight(Node *p) {
    p->height = 1 + max(Node::Stature(p->lc), Node::Stature(p->rc));
  }

  static void UpdateNumAbove(Node *p) {
    while (p) {
      UpdateNum(p);
      p = p->pa;
    }
  }

  static void UpdateNum(Node *p) {
    p->lnum = p->lc ? p->lc->Num() : 0;
    p->rnum = p->rc ? p->rc->Num() : 0;
  }

  // <指针引用, 父指针>
  pair<Node *&, Node *> search(int value) {
    if (!root || root->value == value) return {root, nullptr};
    Node *p = root, *pp = p;
    while (true) {
      if (!p) {  // 节点不存在
        if (value < pp->value) {
          return {pp->lc, pp};
        } else {
          return {pp->rc, pp};
        }
      } else if (value > p->value) {
        pp = p;
        p = p->rc;
      } else if (value < p->value) {
        pp = p;
        p = p->lc;
      } else {  // 节点存在
        return {FromParentTo(p), pp};
      }
    }
  }

  inline Node * &FromParentTo(Node *p) {
    return IsRoot(p) ? root :
           (IsLc(p)) ? p->pa->lc : p->pa->rc;
  }

  inline static bool IsLc(Node *p) {
    return !IsRoot(p) && p->pa->lc == p;
  }

  inline static bool IsRc(Node *p) {
    return !IsRoot(p) && p->pa->rc == p;
  }

  inline static bool IsRoot(Node *p) {
    return !(p->pa);
  }

  inline static int BalFac(Node *p) {
    return Node::Stature(p->lc) - Node::Stature(p->rc);
  }

  inline static bool Balanced(Node *p) {
    return  -2 < BalFac(p) && BalFac(p) < 2;
  }

  Node *Rotate(Node *v) {
    Node *p = v->pa;
    Node *g = p->pa;

    if (IsLc(p)) {
      if (IsLc(v)) {  // LL
        p->pa = g->pa;
        return Connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
      } else {        // LR
        v->pa = g->pa;
        return Connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
      }
    } else {
      if (IsRc(v)) {  // RR
        p->pa = g->pa;
        return Connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
      } else {        // RL
        v->pa = g->pa;
        return Connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
      }
    }
  }

  static Node *Connect34(Node *lt, Node *r, Node *rt,
                         Node *t1, Node *t2, Node *t3, Node *t4) {
    lt->lc = t1; if (t1) t1->pa = lt;
    lt->rc = t2; if (t2) t2->pa = lt;
    rt->lc = t3; if (t3) t3->pa = rt;
    rt->rc = t4; if (t4) t4->pa = rt;

    lt->pa = r; r->lc = lt;
    rt->pa = r; r->rc = rt;

    UpdateHeight(lt);
    UpdateHeight(rt);
    UpdateHeight(r);

    UpdateNum(lt);
    UpdateNum(rt);
    UpdateNum(r);

    return r;
  }

  inline int Num() {
    return root->Num();
  }
  inline Node *Root() {
    return root;
  }

 private:
  Node *root;
};


class MedianFinder {
 public:
    MedianFinder() : avl() {}

    void addNum(int num) {
      avl.add(num);
    }

    double findMedian() {
      int size = avl.Num();
      if (size % 2) {
        return num((size + 1) / 2);
      } else {
        int l = num(size / 2);
        int r = num(size / 2 + 1);
        return (r + l) * 1.0 / 2;
      }
    }

    int num(int order) {
      Node *p = avl.Root();
      int lo = 1;
      int hi = avl.Num();
      int ml, mh;

      while (true) {
        ml = lo + p->lnum - 1;
        mh = hi - p->rnum + 1;
        if (mh <= order && order <= hi) {
          p = p->rc;
          lo = mh;
        } else if (lo <= order && order <= ml) {
          p = p->lc;
          hi = ml;
        } else {
          return p->value;
        }
      }
    }

 private:
  AvlTree avl;
};


void test1() {
  MedianFinder medianFinder;
  medianFinder.addNum(1);                    // arr = [1]
  medianFinder.addNum(2);                    // arr = [1, 2]
  cout << medianFinder.findMedian() << "\n"; // return 1.5 (i.e., (1 + 2) / 2)
  medianFinder.addNum(3);                    // arr[1, 2, 3]
  cout << medianFinder.findMedian() << "\n"; // return 2.0
}

void test2() {
  MedianFinder medianFinder;
  medianFinder.addNum(-1);
  medianFinder.addNum(-2);
  medianFinder.addNum(-3);
  medianFinder.addNum(-4);
  cout << medianFinder.findMedian() << "\n";
  medianFinder.addNum(-5);
  cout << medianFinder.findMedian() << "\n";
}

int main() {
  test2();
  return 0;
}
