#include <utility>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  explicit ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
 public:
  static int ListStrlen(ListNode *head) {
    int n = 0;
    while (head) {
      ++n;
      head = head->next;
    }
    return n;
  }

  static ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    int la = ListStrlen(headA);
    int lb = ListStrlen(headB);

    if (la > lb) {
      swap(headA, headB);
      swap(la, lb);
    }

    /**
     *           a b c d e
     *     1 2 3 4 b c d e
     */
    int n = lb - la;
    for (int i = 0; i < n; ++i) {
      headB = headB->next;
    }
    while (headB && headB != headA) {
      headB = headB->next;
      headA = headA->next;
    }
    return headB ? headB : nullptr;
  }
};