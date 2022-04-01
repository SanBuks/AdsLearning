#include <memory>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  static ListNode *reverseBetween(ListNode *head, int left, int right) {
    unique_ptr<ListNode> up(new ListNode(-1, head));
    auto dummy_head = up.get();

    int num = right - left + 1;

    auto lp = dummy_head;  // 指向 left - 1
    while (--left) {
      lp = lp->next;
    }

    auto pp = lp->next;   // 指向 left
    auto p = pp->next;    // 指向 left + 1

    while (--num) {                 // p 向右移动 num - 1 指向 right + 1
      auto temp = p->next;
      p->next = pp;
      pp = p;
      p = temp;
    }

    lp->next->next = p;
    lp->next = pp;
    return dummy_head->next;
  }
};


int main() {


  return 0;
}