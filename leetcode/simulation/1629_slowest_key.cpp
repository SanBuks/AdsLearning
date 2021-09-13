#include <vector>
#include <string>
using namespace std;

/*
 * easy 画家算法
 */
class Solution {
 public:
  char slowestKey(vector<int> &releaseTimes, string keysPressed) {
    int slowest_time = releaseTimes[0];
    size_t slowest_index = 0;
    for (size_t i = releaseTimes.size() - 1; i != 0; --i) {
      releaseTimes[i] = releaseTimes[i] - releaseTimes[i - 1];
      if (releaseTimes[i] > slowest_time) {
        slowest_time = releaseTimes[i];
        slowest_index = i;
      }
      if (releaseTimes[i] == slowest_time &&
          keysPressed[i] >= keysPressed[slowest_index]) {
        slowest_time = releaseTimes[i];
        slowest_index = i;
      }
    }
    return keysPressed[slowest_index];
  }
};
