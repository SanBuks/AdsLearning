#include <vector>

using namespace std;

class Solution {
 public:
  double average(vector<int> &salary) {
    int min = 1000000, max = 999;
    unsigned sum = 0;
    for (const auto &item : salary) {
      max = item > max ? item : max;
      min = item < min ? item : min;
      sum += item;
    }
    sum -= min + max;
    return sum * 1.0 / static_cast<double>(salary.size() - 2);
  }
};