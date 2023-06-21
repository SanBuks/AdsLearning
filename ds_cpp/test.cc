#include <iostream>
#include <cstring>
#include <chrono>
#include <vector>
#include <string>
#include <random>
#include <stack>
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
  vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> ans;
    if (!root) return ans;

    queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
      auto size = queue.size();
      vector<int> level;
      for (size_t i = 0; i != size; ++i) {
        auto p = queue.front(); queue.pop();
        level.push_back(p->val);
        if (p->left) queue.push(p->left);
        if (p->right) queue.push(p->right);
      }
      ans.push_back(level);
    }
    return ans;
  }
};

int main() {
  return 0;
}