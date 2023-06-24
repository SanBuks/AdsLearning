#include <iostream>
#include <queue>

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
  TreeNode *invertTree(TreeNode *root) {
    if (!root) return nullptr;
    queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto size = queue.size();
      for (size_t i = 0; i != size; ++i) {
        auto p = queue.front(); queue.pop();
        swap(p->left, p->right);
        if (p->left) queue.push(p->left);
        if (p->right) queue.push(p->right);
      }
    }
    return root;
  }
};