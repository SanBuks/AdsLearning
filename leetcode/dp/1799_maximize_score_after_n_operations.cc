#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int GcdCn(int a, int b) {
  if (a == 0 || b == 0) {
    return a == 0 ? b : a;
  }

  int p = 0;
  while (!(a & 1) && !(b & 1)) {
    a >>= 1;
    b >>= 1;
    ++p;
  }

  while (true) {
    while (!(a & 1)) {
      a >>= 1;
    }
    while (!(b & 1)) {
      b >>= 1;
    }

    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }

    if (a == 0) {
      return b << p;
    }
    if (b == 0) {
      return a << p;
    }
  }
}

class Solution {
 public:
  static int dp_[1 << 14];
  static int gcd_[14][14];

  static int Dfs(vector<int> &nums, int mask, int operation, int *dp, int (*gcd)[14]) {
    int size = static_cast<int>(nums.size());

    if (operation >= size / 2) return 0;
    if (dp[mask] != -1) return dp[mask];

    int max_num = 0;
    for (int i = 0; i < size; ++i) {
      if ((mask >> i & 1) == 1) continue;
      for (int j = i + 1; j < size; ++j) {
        if ((mask >> j & 1) == 1) continue;
        int score = gcd[i][j] * (operation + 1);
        auto new_mask = mask | 1 << i | 1 << j;
        int temp = Dfs(nums, new_mask, operation + 1, dp, gcd);
        max_num = max(max_num, score + temp);
      }
    }
    return dp[mask] = max_num;
  }

  static int maxScore(vector<int> &nums) {
    auto size = static_cast<int>(nums.size());
    auto max_mask = 1 << size;
    memset(dp_, -1, sizeof(dp_));
    memset(gcd_, 0, sizeof(gcd_));

    for (int i = 0; i < size; ++i) {
      for (int j = i + 1; j < size; ++j) {
        gcd_[i][j] = GcdCn(nums[i], nums[j]);
      }
    }
    return Dfs(nums, 0, 0, dp_, gcd_);
  }
};

int Solution::dp_[1 << 14];
int Solution::gcd_[14][14];

int main() {
  vector<int> nums{39759,619273,859218,228161,944571,597983,483239,179849,868130,909935,912143,817908,738222,653224};

  std::cout << Solution::maxScore(nums);
  return 0;
}
