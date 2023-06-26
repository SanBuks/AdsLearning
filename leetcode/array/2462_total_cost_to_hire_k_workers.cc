#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
 public:
  long long totalCost(vector<int> &costs, int k, int candidates) {
    long long sum = 0;
    priority_queue<int, vector<int>, greater<>> lheap;
    priority_queue<int, vector<int>, greater<>> rheap;

    int lo = -1, hi = static_cast<int>(costs.size());
    // 初始化左右堆
    for (int i = 0; i < candidates; ++i) {
      ++lo; --hi;
      if (hi < lo) break;
      if (hi == lo) { lheap.push(costs[lo]); break; }
      lheap.push(costs[lo]);
      rheap.push(costs[hi]);
    }

    // 遍历 k
    for (int i = 0; i < k; ++i) {
      if (lheap.empty() || (!rheap.empty() && lheap.top() > rheap.top())) {
        sum += rheap.top();
        rheap.pop();
        --hi;
        if (hi == lo || hi < lo) continue;
        else rheap.push(costs[hi]);
      } else {
        sum += lheap.top();
        lheap.pop();
        ++lo;
        if (hi == lo || hi < lo) continue;
        else lheap.push(costs[lo]);
      }
    }

    return sum;
  }
};

int main() {
  Solution sol;

  vector<int> vec{17, 12, 10, 2, 7, 2, 11, 20, 8};
  cout << sol.totalCost(vec, 3, 4) << "\n";

//  vector<int> vec{1, 2, 4, 1};
//  cout << sol.totalCost(vec, 3, 3) << "\n";


  return 0;
}