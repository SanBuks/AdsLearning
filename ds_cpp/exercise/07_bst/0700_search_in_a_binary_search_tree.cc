struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  TreeNode *searchBST(TreeNode *root, int val) {
    return find(root, val);
  }

  TreeNode *find(TreeNode *root, int val) {
    if (!root || root->val == val) {
      return root;
    }

    while (root) {
      if (val == root->val) {
        return root;
      }
      if (val > root->val) {
        root = root->right;
      } else {
        root = root->left;
      }
    }
    return root;
  }

};