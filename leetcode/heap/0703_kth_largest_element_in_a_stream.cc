#include <vector>
#include <queue>
using namespace std;
class KthLargest {
 public:
  priority_queue<int, vector<int>, greater<int>> queue_;
  int kk;
  KthLargest(int k, vector<int> &nums) {
    kk = k;
   while (!queue_.empty()) queue_.pop();
   for (const auto &item : nums) {
     queue_.push(item);
     if (queue_.size() > k) {
       queue_.pop();
     }
   }
  }

  int add(int val) {
    queue_.push(val);
    if (queue_.size() > kk) {
      queue_.pop();
    }
    return queue_.top();
  }
};