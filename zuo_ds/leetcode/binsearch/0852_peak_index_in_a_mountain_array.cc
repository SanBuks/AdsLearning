#include <vector>
using namespace std;
class Solution {
 public:
  int peakIndexInMountainArray(vector<int> &arr) {
    int size = static_cast<int>(arr.size());

    if (arr[0] > arr[1]) return 0;
    if (arr[size - 1] > arr[size - 2]) return size - 1;

    int lo = 1;
    int hi = size - 1;

    while (lo < hi) {
      int mi = lo + (hi - lo) / 2;
      if (arr[mi] < arr[mi + 1]) {
        lo = mi + 1;
      } else if (arr[mi] < arr[mi - 1]) {
        hi = mi;
      } else {
        return mi;
      }
    }
    return 0;
  }
};