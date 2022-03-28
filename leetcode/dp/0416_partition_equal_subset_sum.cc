#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * 0-1 背包问题 二维 DP
 * @param weight 物品重量
 * @param value 物品价值
 * @param capacity 容量
 * @return
 */
int Bag2D(vector<int> &weight, vector<int> &value, int capacity) {
  // dp[i] 表示 0 - i 个物品考虑在内
  // dp[x][i] 表示 0 - x 个物品, 容量为 i 的最大价值
  vector<vector<int>> dp(weight.size(), vector<int>(capacity + 1, 0));
  size_t num = weight.size();  // 物品总量
  for (int i = capacity; i >= weight[0]; --i) {
    dp[0][i] = value[0];
  }
  for (int i = 0; i < num; ++i) {
    dp[i][0] = 0;
  }

  for (int i = 1; i < num; ++i) {
    for (int j = 1; j <= capacity; ++j) {
      if (j - weight[i] >= 0) {
        dp[i][j] = max(dp[i - 1][j], value[i] + dp[i - 1][j - weight[i]]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return dp[num - 1][capacity];
}

/**
 * 0-1 背包问题 一维 动态数组
 * @param weight 物品重量
 * @param value 物品价值
 * @param capacity 容量
 * @return
 */
int BagArray(vector<int> &weight, vector<int> &value, int capacity) {
  vector<int> dp(capacity + 1, 0);
  size_t num = weight.size();

  for (int j = 0; j < num; ++j) {
    for (int i = capacity; i >= weight[j]; --i) {
      dp[i] = max(dp[i], value[j] + dp[i - weight[j]]);
    }
  }
  return dp[capacity];
}

class Solution {
 public:
  // 1 <= nums.length <= 200
  // 1 <= nums[i] <= 100
  static bool canPartition(vector<int> &nums) {
    int sum = 0;
    for (const auto &item : nums) {
      sum += item;
    }
    if (sum & 1) {
      return false;
    }
    sum >>= 1;

    size_t num = nums.size();
    vector<int> dp(sum + 1, 0);

    for (int j = 0; j < num; ++j) {
      for (int i = sum; i >= nums[j]; --i) {
        dp[i] = max(dp[i], nums[j] + dp[i - nums[j]]);
      }
    }
    return dp[sum] == sum;
  }
};

void BagTest() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int capacity = 4;
  std::cout << Bag2D(weight, value, capacity) << "\n";
  std::cout << BagArray(weight, value, capacity) << "\n";
}


int main() {
//  vector<int> vec{1,5,11,5};
  vector<int> vec{1,2,3,5};
  std::cout << Solution::canPartition(vec);
//  BagTest();
}
