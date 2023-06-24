#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  long long minCost(vector<int> &nums, vector<int> &cost) {
    if (nums.size() == 1) return 0;

    int lo = numeric_limits<int>::max();
    int hi = numeric_limits<int>::min();
    for (auto &item : nums) {
      lo = min(lo, item);
      hi = max(hi, item);
    }

    long long left = co(nums, cost, lo);
    long long right = co(nums, cost, lo + 1);
    long long mid;
    if (left <= right) {
      return left;
    }

    left = co(nums, cost, hi - 1);
    right = co(nums, cost, hi);

    if (left >= right) {
      return right;
    }

    ++lo;
    while (lo < hi) {
      int mi = lo + (hi - lo) / 2;
      left = co(nums, cost, mi - 1);
      mid = co(nums, cost, mi);
      if (left >= mid) {
        lo = mi + 1;
      } else {
        hi = mi;
      }
    }
    return co(nums, cost, --lo);
  }

  long long co(vector<int> &nums, vector<int> &cost, int target) {
    long long sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      long long delta = abs(nums[i] - target);
      sum += delta * cost[i];
    }
    return sum;
  }
};


int main() {
  Solution sol;
//  vector<int> nums{1, 3, 5, 2};
//  vector<int> cost{2, 3, 1, 14};

  vector<int> nums{2, 2, 2, 2, 2};
  vector<int> cost{4, 2, 8, 1, 3};
  cout << sol.minCost(nums, cost) << "\n";

  return 0;
}