#include <vector>
#include <stack>
#include <queue>
#include <utility>

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
  vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> res;
    if (!root) return res;

    queue<TreeNode *> queue;
    queue.push(root);

    while (!queue.empty()) {
      vector<int> vec;
      auto size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto p = queue.front(); queue.pop();
        vec.push_back(p->val);
        if (p->left) queue.push(p->left);
        if (p->right) queue.push(p->right);
      }
      res.push_back(std::move(vec));
    }
    return res;
  }
};