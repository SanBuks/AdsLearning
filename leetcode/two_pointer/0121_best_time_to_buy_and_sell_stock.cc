#include <vector>

using namespace std;

/**
 *  easy 时刻更新区间最小值
 */
class Solution {
 public:
  int maxProfit(vector<int> &prices) {
    int max = static_cast<int>(prices.size());
    int i = 0, j = 1;
    int result = 0;
    // i 永远指向区间的最低值
    while (j < max) {
      auto temp = prices[j] - prices[i];
      if (temp > 0) {
        result = (temp > result) ? temp : result;
        ++j;
      } else {
        i = j;
        j = j + 1;
      }
    }
    return result;
  }
};
