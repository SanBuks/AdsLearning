#include <deque>
#include <vector>
#include <iostream>

using namespace std;

class MyQueue {
 public:
  MyQueue() = default;

  int &Front() {
    return de_.front();
  }

  void Pop() {
    de_.pop_front();
  }

  void Push(int num) {
    while (!de_.empty() && de_.back() < num) {
      de_.pop_back();
    }
    de_.push_back(num);
  }

 private:
  deque<int> de_;
};

class Solution {
 public:
  static vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    vector<int> res;
    MyQueue mq;

    size_t size = nums.size();

    for (int i = 0; i < k && i < size; ++i) {
      mq.Push(nums[i]);
    }
    res.push_back(mq.Front());

    for (int i = k; i < size; ++i) {
      auto pop_item = nums[i - k];
      if (pop_item == mq.Front()) {
        mq.Pop();
      }
      mq.Push(nums[i]);
      res.push_back(mq.Front());
    }

    return res;
  }
};

int main() {
  vector<int> vec{1,-1};
  int k = 1;
//  vector<int> vec{1, 3, -1, -3, 5, 3, 6, 7};
//  int k = 3;
  auto v = Solution::maxSlidingWindow(vec, k);
  for (auto &item: v) {
    cout << item << " ";
  }
  cout << "\n";
  return 0;
}