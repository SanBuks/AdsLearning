#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
 public:
  static int lastStoneWeightII(vector<int> &stones) {
    int sum = 0;
    for (auto item : stones) { sum += item; }
    int max_size = sum >> 1;

    vector<int> dp(sum + 1, 0);
    for (const auto &value : stones) {
      for (int j = max_size; j >= value; --j) {
        dp[j] = max(dp[j], value + dp[j - value]);
      }
    }

    return sum - dp[max_size] - dp[max_size];
  }
};

int main() {
  vector<int> vec{31,26,33,21,40};
  std::cout << Solution::lastStoneWeightII(vec) << "\n";
  return 0;
}
