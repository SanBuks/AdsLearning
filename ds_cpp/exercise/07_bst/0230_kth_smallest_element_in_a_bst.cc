#include <stack>
using namespace std;
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
  int kthSmallest(TreeNode *root, int k) {
    stack<TreeNode *> st;

    auto p = root;
    while (true) {
      if (p) {
        st.push(p);
        p = p->left;
      } else if (!st.empty()){
        p = st.top(); st.pop();
        if (--k == 0) return p->val;
        p = p->right;
      } else {
        break;
      }
    }
  }
};