/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <limits>
#include <algorithm>

using namespace std;

class Solution {
 public:
  int min_;

  int getMinimumDifference(TreeNode *root) {
    min_ = numeric_limits<int>::max();
    int pre = -1;
    InOrderTraverse(root, pre);
    return min_;
  }

  void InOrderTraverse(TreeNode *pos, int &pre) {
    if (pos->left) {
      InOrderTraverse(pos->left, pre);
    }

    int val = pos->val;
    if (pre >= 0) {
      min_ = min(min_, val - pre);
    }
    pre = val;

    if (pos->right) {
      InOrderTraverse(pos->right, pre);
    }
  }
};
