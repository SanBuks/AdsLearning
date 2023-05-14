#include<vector>
using namespace std;
class Solution {
 public:
  static const int kPoint = 0;
  static const int kBrainPower = 1;

  long long static mostPoints(vector<vector<int>> &questions) {
    int size = static_cast<int>(questions.size());
    vector<long long> dp(size + 1, 0);
    for (int i = size - 1; i >= 0; --i) {
      int last_dp_index = min(size, i + questions[i][kBrainPower] + 1);
      dp[i] = max(dp[i + 1], questions[i][kPoint] + dp[last_dp_index]);
    }
    return dp[0];
  }
};

int main () {

  return 0;
}