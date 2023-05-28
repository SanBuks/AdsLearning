#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

class Solution {
 public:
  int bit_sum[sizeof(int) * 8];
  int singleNumber(vector<int> &nums) {
    int k = 1, m = 3;
    std::memset(bit_sum, 0, sizeof(bit_sum));
    constexpr const int width = sizeof(int) * 8;

    for (const auto &num : nums) {
      for (int i = 0; i < width; ++i) {
        if (num & (1 << i)) {
          ++bit_sum[i];
        }
      }
    }

    for (auto & i : bit_sum) {
      i = i % m ? -1 : 0;
    }

    int result = 0; unsigned int weight = 1;
    for (int i : bit_sum) {
      if (i) {
        // 左移为了防止出现负数, 一般采用无符号然后进行强转
        result += static_cast<int>(weight);
      }
      weight <<= 1;
    }
    return result;
  }
};

int main() {
  vector<int> nums{0, 1, 0, 1, 0, 1, 99};
  Solution sol;
  cout << sol.singleNumber(nums) << "\n";
  return 0;
}