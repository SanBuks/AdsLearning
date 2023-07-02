#include <algorithm>
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
  TreeNode *parent;
  TreeNode *deleteNode(TreeNode *root, int key) {
    if (!root) return nullptr;

    TreeNode * &ref = searchNodeRef(root, key);
    TreeNode * target = ref;
    TreeNode * succ = nullptr;

    if (!ref) {
      return root;
    }
    if (!ref->left) {
      ref = succ = ref->right;
      delete target;
    } else if (!ref->right) {
      ref = succ = ref->left;
      delete target;
    } else {
      // 找到中序后继 (一定存在)
      // 删除节点
      target = succRight(ref);
      // 替换数值
      std::swap(target->val, ref->val);
      // 替换节点
      succ = target->right;
      if (parent == ref) {
        parent->right = succ;
      } else {
        parent->left = succ;
      }
      delete target;
    }
    return root;
  }


  TreeNode * &searchNodeRef(TreeNode *&root, int key) {
    if (!root || root->val == key) {
      parent = nullptr;
      return root;
    }

    for (parent = root;;) {
      TreeNode * &ref = key > parent->val ?  parent->right : parent->left;
      if (!ref || ref->val == key) { return ref; }
      parent = ref;
    }
  }

  TreeNode *succRight(TreeNode *p) {
    parent = p;
    if (!p->right) {
      return nullptr;
    }
    p = p->right;
    while (p->left) {
      parent = p;
      p = p->left;
    }
    return p;
  }

};

int main() {

  TreeNode *root = new TreeNode(5);

  auto l1 = root->left = new TreeNode(3);
  auto r2 = root->right = new TreeNode(6);

  auto l1l = l1->left = new TreeNode(2);
  auto l1r = l1->right = new TreeNode(4);

  auto r1r = r2->left = new TreeNode(7);

  Solution sol;
  sol.deleteNode(root, 3);

  return 0;
}