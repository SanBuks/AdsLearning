#include <string>
#include <deque>

using namespace std;

class Solution {
 public:
  static string predictPartyVictory(const string &senate) {
    auto size = static_cast<int>(senate.size());

    deque<int> rq;
    deque<int> dq;

    for (int i = 0; i < size; ++i) {
      if (senate[i] == 'R') {
        rq.push_back(i);
      } else {
        dq.push_back(i);
      }
    }

    while (!rq.empty() && !dq.empty()) {
      if (rq.front() < dq.front()) {
        rq.push_back(rq.front() + size);
        rq.pop_front();
        dq.pop_front();
      } else {
        dq.push_back(dq.front() + size);
        dq.pop_front();
        rq.pop_front();
      }
    }
    return !rq.empty() ? "Radiant" : "Dire";
  }
};