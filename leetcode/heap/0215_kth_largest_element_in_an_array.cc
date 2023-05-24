#include <vector>
#include <queue>
using namespace std;
class Solution {
 public:
  priority_queue<int, vector<int>, greater<int>> queue_;

  int findKthLargest(vector<int> &nums, int k) {
    for (const auto &item : nums) {
      queue_.push(item);
      if (queue_.size() > k) {
        queue_.pop();
      }
    }
    return queue_.top();
  }
};