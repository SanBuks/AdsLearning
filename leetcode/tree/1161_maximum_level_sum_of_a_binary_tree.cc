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

#include <queue>
#include <vector>
using namespace std;
class Solution {
 public:
  int maxLevelSum(TreeNode *root) {
    queue<TreeNode*> queue;
    int level = 1; int sum;
    pair<int, int> record{1, root->val};
    if (root->left) queue.push(root->left);
    if (root->right) queue.push(root->right);
    while (!queue.empty()) {
      ++level; sum = 0;
      size_t size = queue.size();
      for (int i = 0; i < size; ++i) {
        auto p = queue.front();
        sum += p->val;
        if (p->left) { queue.push(p->left); }
        if (p->right) { queue.push(p->right); }
        queue.pop();
      }
      if (sum > record.second) {
        record.first = level;
        record.second = sum;
      }
    }
    return record.first;
  }
};

int main(){

  return 0;
}