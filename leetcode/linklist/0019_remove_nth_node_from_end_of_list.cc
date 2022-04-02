#include <memory>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// The number of nodes in the list is sz.
// 1 <= sz <= 30
// 0 <= Node.val <= 100
// 1 <= n <= sz
class Solution {
 public:
  static ListNode *removeNthFromEnd(ListNode *head, int n) {
    auto p = head;

    for (int i = 0; i < n - 1; ++i) {
      p = p->next;
    }

    auto pp = head;
    decltype(pp) ppp = nullptr;

    while (p->next) {
      p = p->next;
      ppp = pp;
      pp = pp->next;
    }

    if (!ppp) {
      auto temp = head;
      head = head->next;
    } else {
      ppp->next = pp->next;
    }
    return head;
  }
};
