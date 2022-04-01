struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
 public:
  // 双指针
  static ListNode *reverseList1(ListNode *head) {
    ListNode *pp = nullptr, *p = head;
    while (p) {
      auto next = p->next;
      p->next = pp;
      pp = p;
      p = next;
    }
    return pp;
  }

//  static ListNode *next_head;

  // 递归
  static ListNode *reverseList2(ListNode *head) {
    if (!head) {
      return head;
    }
    ListNode *next_head;
    auto p = reverse(head, next_head);
    p->next = nullptr;
    return next_head;
  }

  static ListNode *reverse(ListNode *p, ListNode * &next_head) {
    if (!p->next) {
      next_head = p;
      return p;
    }
    auto p_next = reverse(p->next, next_head);
    p_next->next = p;
    return p;
  }
};

//ListNode * Solution::next_head;

int main( ){

  auto p5 = new ListNode(5);
  auto p4 = new ListNode(4, p5);
  auto p3 = new ListNode(3, p4);
  auto p2 = new ListNode(2, p3);
  auto p1 = new ListNode(1, p2);
  auto p = Solution::reverseList2(p1);

  return 0;
}