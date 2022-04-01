#include <memory>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  // 虚拟头节点
  static ListNode *removeElements1(ListNode *head, int val) {
    std::unique_ptr<ListNode> dummy_head(new ListNode(-1, head));
    auto p = dummy_head.get();
    while (p->next) {
      if (p->next->val == val) {
        auto temp = p->next;
        p->next = p->next->next;
        delete temp;
      } else {
        p = p->next;
      }
    }
    return dummy_head->next;
  }
  // 首先对头节点进行处理
  static ListNode *removeElements2(ListNode *head, int val) {
    while (head && head->val == val) {
      auto temp = head;
      head = head->next;
      delete temp;
    }

    auto p = head;
    while(p && p->next) {
      if (p->next->val == val) {
        auto temp = p->next;
        p->next = p->next->next;
        delete temp;
      } else {
        p = p->next;
      }
    }
    return head;
  }
};