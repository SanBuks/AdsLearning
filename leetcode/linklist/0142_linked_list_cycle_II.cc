using namespace std;

/**
 * (s - m) % c = (2s - m) % c = r
 * =>
 *  s - m = ac + r
 * 2s - m = bc + r
 * =>
 *  m = (b - 2a)c - r
 *    = (b - 2a - 1)c + c - r
 * =>
 *  c - r = m % c => m = kc + c -r
 */

struct ListNode {
  int val;
  ListNode *next;
  explicit ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
 public:
  static ListNode *detectCycle(ListNode *head) {
    if (!head || !head->next || !head->next->next) {
      return nullptr;
    }

    auto pp = head->next;
    auto p = pp->next;
    while (p != pp) {
      pp = pp->next;

      p = p->next;

      if (!p) {
        return nullptr;
      }
      p = p->next;
      if (!p) {
        return nullptr;
      }
    }

    auto q = head;
    while (q != p) {
      q = q->next;
      p = p->next;
    }
    return q;
  }
};
