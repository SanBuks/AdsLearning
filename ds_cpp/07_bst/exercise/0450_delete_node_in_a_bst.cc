#include <utility>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
 public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    TreeNode *r = root;
    auto &ref = searchRef(root, key, r);
    if (!ref) return r;

    auto p = ref;
    if (!p->left) {
      ref = p->right;
      delete p;
    } else if(!p->right) {
      ref = p->left;
      delete p;
    } else {
      TreeNode *succpp;
      auto succ = successor(p, succpp);
      std::swap(succ->val, p->val);

      if (succ == p->right) {
        succpp ->right = succ->right;
        delete succ;
      } else {
        succpp->left= succ->right;
        delete succ;
      }
    }
    return r;
  }

  TreeNode *successor(TreeNode *p, TreeNode *&pp) {
    if (!p || !p->right) {
      pp = nullptr;
      return nullptr;
    }
    pp = p;
    p = p->right;
    while (p->left) {
      pp = p;
      p = p->left;
    }
    return p;
  }

  TreeNode * &searchRef(TreeNode *p, int val, TreeNode * &r) {
    if (!p || p->val == val) return r;
    while (true) {
      if (val < p->val) {
        if (!p->left || p->left->val == val) return p->left;
        p = p->left;
      } else {
        if (!p->right || p->right->val == val) return p->right;
        p = p->right;
      }
    }
  }
};
//leetcode submit region end(Prohibit modification and deletion)