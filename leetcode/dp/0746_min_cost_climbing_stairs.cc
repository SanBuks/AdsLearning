#include <vector>

using namespace std;

class Solution {
 public:
  static int minCostClimbingStairs2(vector<int>& cost) {
    cost.push_back(0);
    size_t size = cost.size();
    for (size_t i = 2; i < size; ++i) {
      cost[i] = cost[i - 1] < cost [i - 2] ? cost[i - 1] + cost[i] : cost[i - 2] + cost[i];
    }
    return cost[size - 1];
  }

  static int minCostClimbingStairs(vector<int>& cost) {
    cost.push_back(0);
    auto size = cost.size();
    int pre = cost[0], now = cost[1], tmp;
    for (int i = 2; i < size; ++i) {
      tmp = cost[i] + (now < pre ? now : pre);
      pre = now;
      now = tmp;
    }
    return now;
  }
};
