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
  static constexpr int pair_size = 2;

  // (lo, hi]
  static void reverse(ListNode *lo, ListNode *hi) {
    auto right = hi->next;
    auto pp = lo->next;
    auto p = pp->next;

    while (p != right) {
      auto temp = p->next;
      p->next = pp;
      pp = p;
      p = temp;
    }

    lo->next->next = p;
    lo->next = pp;
  }

  static ListNode *swapPairs(ListNode *head) {
    unique_ptr<ListNode> up_(new ListNode(0, head));
    auto dummy_head = up_.get();
    auto pp = dummy_head;
    auto p = pp;

    while (true) {
      for (int i = 0; i < pair_size && p!= nullptr; ++i) {
        p = p->next;
      }
      if (!p) {
        break;
      } else {
        // 交换区间
        reverse(pp, p);
        // 更新 pp 和 p
        for (int i = 0; i < pair_size; ++i) {
          pp = pp->next;
        }
        p = pp;
      }
    }

    return dummy_head->next;
  }
};

constexpr int Solution::pair_size;