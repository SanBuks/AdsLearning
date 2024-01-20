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
  TreeNode *searchBST(TreeNode *root, int val) {
    while (root) {
      if (root->val == val) {
        return root;
      } else if (val < root->val) {
        root = root->left;
      } else {
        root = root->right;
      }
    }
    return root;
  }
};
//leetcode submit region end(Prohibit modification and deletion)