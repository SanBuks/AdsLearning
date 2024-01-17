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
  vector<int> preorderTraversal(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> stack;
    auto visit_along_left = [&stack, &res](TreeNode *p) {
      while (p) {
        res.push_back(p->val);
        if (p->right) stack.push(p->right);
        p = p->left;
      }
    };

    visit_along_left(root);
    while (!stack.empty()) {
      auto p = stack.top(); stack.pop();
      visit_along_left(p);
    }
    return res;
  }
};