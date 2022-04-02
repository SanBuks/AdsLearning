#include <memory>

using namespace std;
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  // size [0, 104]
  static bool hasCycle(ListNode *head) {
    if (!head || !head->next) {
      return false;
    }
    auto p = head;
    auto pp = p->next;
    while (pp != p) {
      p = p->next;
      pp = pp->next;
      if (!pp) {
        return false;
      }
      pp = pp->next;
      if (!pp) {
        return false;
      }
    }
    return true;
  }
};