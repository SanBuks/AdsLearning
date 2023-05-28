#include <vector>
#include <limits>
#include <iostream>
using namespace std;
class Solution {
 public:
  vector<int> singleNumber(vector<int> &nums) {
    int item1 = 0;
    for (const int &num : nums) {
      item1 ^= num;
    }

    int right_one = item1 & (item1 == numeric_limits<int>::min() ? 1 : -item1);
    int item2 = 0;
    for (const int &num : nums) {
      if (num & right_one) {
        item2 ^= num;
      }
    }

    item1 ^= item2;
    return {item1, item2};
  }
};

int main() {
  cout << numeric_limits<int>::min() << "\n";
  return 0;
}