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
  vector<int> inorderTraversal(TreeNode *root) {
    stack<TreeNode *> stack;
    vector<int> res;

    auto go_along_left = [&stack](TreeNode *p) {
      while (p) {
        stack.push(p);
        p = p->left;
      }
    };

    go_along_left(root);
    while (!stack.empty()) {
      auto val = stack.top(); stack.pop();
      res.push_back(val->val);
      if (val->right) go_along_left(val->right);
    }
    return res;
  }
};
