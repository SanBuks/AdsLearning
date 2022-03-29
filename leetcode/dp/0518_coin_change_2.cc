#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static int change(int amount, vector<int> &coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    /**
     * 先 capacity 再 weight 是全排列的个数
     */
//    for (int i = 1; i <= amount; ++i) {
//      for (int j = 0; j < coins.size(); ++j) {
//        if (i - coins[j] >= 0) {
//          dp[i] += dp[i - coins[j]];
//        }
//      }
//    }

    /**
     * 先 weight 再 capacity 是组合的个数
     */
    for (int j = 0; j < coins.size(); ++j) {
      for (int i = 1; i <= amount; ++i) {
        if (i - coins[j] >= 0) {
          dp[i] += dp[i - coins[j]];
        }
      }
    }
    return dp[amount];
  }
};

/**
 * 完全背包问题
 * @param weight 物品重量
 * @param value 物品价值
 * @param capacity 容量
 */
int BagComplete(vector<int> weight, vector<int> value, int capacity) {
  vector<int> dp(capacity + 1, 0);
  size_t num = weight.size();
  /**
   * 先 capacity 再 weight 或 反之都是相同
   */
  for (int i = 0; i <= capacity; ++i) {
    for (int j = 0; j < num; ++j) {
      if (i - weight[j] >= 0) {
        dp[i] = max(dp[i], dp[i -weight[j]] + value[j]);
      }
    }
  }
  return dp[capacity];
}

void BagCompleteTest() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int capacity = 4;
  cout << BagComplete(weight, value, capacity) << "\n";
}

int main() {
  vector<int> vec{1, 2, 5};
  cout << Solution::change(5, vec) << "\n";
//  BagCompleteTest();
  return 0;
}