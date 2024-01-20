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
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    if (!root) {
      root = new TreeNode(val, nullptr, nullptr);
      return root;
    }
    searchRef(root, val) = new TreeNode(val, nullptr, nullptr);
    return root;
  }

  TreeNode * &searchRef(TreeNode *p, int val) {
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