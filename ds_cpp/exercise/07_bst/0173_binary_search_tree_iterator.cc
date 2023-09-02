struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <utility>
using namespace std;

class BSTIterator {
 public:
  BSTIterator(TreeNode *root) : root_(root) {
    pos_ = TraverseAlongLeftVine(root_);
  }

  int next() {
    int ans = pos_->val;
    if (pos_->right) {
      pos_ = TraverseAlongLeftVine(pos_->right);
    } else {
      auto pair_result = GetParentAndSucc(ans);
      auto parent = pair_result.first;
      auto succ = pair_result.second;
      pos_ = (pos_ == parent->left) ? parent : succ;
    }
    return ans;
  }

  bool hasNext() {
    return pos_;
  }

 private:
  TreeNode *TraverseAlongLeftVine(TreeNode *p) {
    if (!p) return p;
    auto pp = p;
    while (p) {
      pp = p;
      p = p->left;
    }
    return pp;
  }
  TreeNode *TraverseAlongRightVine(TreeNode *p) {
    if (!p) return p;
    auto pp = p;
    while (p) {
      pp = p;
      p = p->right;
    }
    return pp;
  }

  pair<TreeNode*, TreeNode *> GetParentAndSucc(int val) {
    TreeNode *succ = nullptr;
    TreeNode *parent = root_;
    TreeNode *p = root_;

    while (p->val != val) {
      parent = p;
      if (val > p->val) {
        p = p->right;
      } else {
        succ = parent;
        p = p->left;
      }
    }

    return {parent, succ};
  }

  TreeNode *root_;
  TreeNode *pos_;
};