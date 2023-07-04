#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

constexpr const int NUM = sizeof(int) * 8;

class Solution {
 public:
  int bit_sum[NUM];
  int singleNumber(vector<int> &nums) {
    int m = 3, k = 1;
    memset(bit_sum, static_cast<unsigned char>(0), sizeof(bit_sum));
    for (auto &num : nums) {
      auto n = static_cast<unsigned int>(num);
      for (int i = 0; i < NUM; ++i) {
        if (n & 1 << i) ++bit_sum[i];
      }
    }

    int target = 0;
    for (int i = 0; i < NUM; ++i) {
      if (bit_sum[i] %= m) {
        target += (1 << i);
      }
    }
    return target;
  }
};


int main() {
  Solution sol;

//  vector<int> vec{0, 1, 0, 1, 0, 1, 99};
  vector<int> vec{2, 2, 3, 2};
  cout << sol.singleNumber(vec) << "\n";
  return 0;
}