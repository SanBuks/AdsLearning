#include <memory>
#include <iostream>
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
  static void Reverse(ListNode *lo, ListNode *hi) {
    if (lo == hi || lo->next == hi) { return ;}
    // 注意 end 必须备份, 因为 p 遍历到最后会改变 hi->next
    auto pp = lo->next, p = pp->next, end = hi->next;
    while (p != end) {
      auto temp = p->next;
      p->next = pp;
      pp = p;
      p = temp;
    }
    lo->next->next = p;
    lo->next = pp;
  }

  static int pairSum(ListNode *head) {
    unique_ptr<ListNode> dummy(new ListNode(-1, head));
    int size = 0;
    auto hi = dummy.get();
    while (hi->next) {
      ++size;
      hi = hi->next;
    }

    auto lo = dummy.get();
    for (int i = 0; i < size / 2; ++i) {
      lo = lo->next;
    }

    Reverse(lo, hi);

    int result = 0;

    auto p = dummy.get(), pp = lo;
    while (pp->next) {
      p = p->next;
      pp = pp->next;
      result = max(p->val + pp->val, result);
    }

    return result;
  }
};

int main() {

  auto head4 = new ListNode(1, nullptr);
  auto head3 = new ListNode(2, head4);
  auto head2 = new ListNode(4, head3);
  auto head1 = new ListNode(5, head2);

  std::cout << Solution::pairSum(head1) << "\n";

  delete head1;
  delete head2;
  delete head3;
  delete head4;

  return 0;
}