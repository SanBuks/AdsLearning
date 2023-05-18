#include <memory>
using namespace std;
struct ListNode {
  int val;
  ListNode *next;

  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode *swapNodes(ListNode *head, int k) {
    unique_ptr<ListNode> dummy(new ListNode(-1, head));
    auto pp = dummy.get();
    auto p = pp;

    for (int i = 0; i < k; ++i) {
      p = p->next;
    }
    auto first = p;

    while (p) {
      pp = pp->next;
      p = p->next;
    }
    swap(first->val, pp->val);
    return head;
  }
};