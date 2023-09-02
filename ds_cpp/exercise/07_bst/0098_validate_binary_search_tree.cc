struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <stack>
#include <limits>

using namespace std;
class Solution {
 public:
  bool isValidBST(TreeNode *root) {
    return Dfs(root, numeric_limits<long long>::min(), numeric_limits<long long>::max());
  }

  bool Dfs(TreeNode *p, long long min, long long max) {
    if (!p) return true;

    if (p->val <= min) return false;
    if (p->val >= max) return false;
    return Dfs(p->left, min, p->val) && Dfs(p->right, p->val, max);
  }

  bool isValidBSTNoRecursion(TreeNode *root) {
    if (!root) return true;
    long long pre = numeric_limits<long long>::min();
    stack<TreeNode *> st;
    auto p = root;
    while (true) {
      if (p) {
        st.push(p);
        p = p->left;
      } else if (!st.empty()) {
        p = st.top(); st.pop();
        if (p->val <= pre) return false;
        else pre = p->val;
        p = p->right;
      } else {
        break;
      }
    }
    return true;
  }

};