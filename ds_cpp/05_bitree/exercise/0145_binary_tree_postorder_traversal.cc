#include <vector>
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
  vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> stack;

    auto go_along_left = [&stack, &res](TreeNode *p) {
      while (p) {
        stack.push(p);
        if (p->right) stack.push(p->right);
        p = p->left;
      }
    };
    go_along_left(root);
    TreeNode *last = nullptr;
    while (!stack.empty()) {
      auto p = stack.top(); stack.pop();
      auto backtrace = last && (last == p->left || last == p->right);
      if (!stack.empty() && (p->left || p->right) && !backtrace) {
        go_along_left(p);
      } else {
        res.push_back(p->val);
        last = p;
      }
    }
    return res;
  }
};
