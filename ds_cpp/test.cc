#include <iostream>
#include <cstring>
#include <chrono>
#include <vector>
#include <string>
#include <random>
#include <stack>
using namespace std;
/**
 * Definition for a binary tree node.
 */

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
    vector<int> ans;
    if (!root) return ans;
    stack<TreeNode *> stack;
    auto go_along_left_vine = [&stack](TreeNode *p) {
      while (p) { stack.push(p); p = p->left; }
    };
    go_along_left_vine(root);
    while (!stack.empty()) {
      auto p = stack.top(); stack.pop();
      ans.push_back(p->val);
      if (p->right) { go_along_left_vine(p->right); }
    }
    return ans;
  }
};

int main() {
  return 0;
}