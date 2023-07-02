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
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    search(root, val) = new TreeNode(val);
    return root;
  }

  TreeNode * &search(TreeNode *&root, int val) {
    if (!root || root->val == val) {
      return root;
    }

    TreeNode * p = root;
    while (true) {
      TreeNode * &ref = val < p->val ? p->left : p->right;
      if (!ref || ref->val == val) return ref;
      p = ref;
    }
  }
};


int main() {
  // 4,2,7,1,3
  TreeNode *root = new TreeNode(4);

  auto l1 = root->left = new TreeNode(2);
  auto r2 = root->right = new TreeNode(7);

  auto l1l = l1->left = new TreeNode(1);
  auto l1r = l1->right = new TreeNode(3);

  Solution sol;
  sol.insertIntoBST(root, 5);

  return 0;
}