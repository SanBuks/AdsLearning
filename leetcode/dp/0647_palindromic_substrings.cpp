#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * [DP : MEDIUM]
 */
size_t dp[1000][1000][2] = {0};

class Solution {
 public:
  int countSubstrings(string str) {
    auto size = str.size();
    for (size_t i = 0; i != size; ++i) {
      dp[i][i][0] = 1;
      dp[i][i][1] = 1;
    }
    for (size_t i = 0; i != size-1; ++i) {
      dp[i][i + 1][1] = 1;
    }

    for (size_t row_index = 1; row_index != size; ++row_index) {
      for (size_t row = row_index, col = 0; row != size; ++row, ++col) {
        if ((dp[row - 1][col + 1][1] == 1) && (str[col] == str[row])) {
          dp[row][col][0] =
              dp[row - 1][col][0] + dp[row][col + 1][0]
                  - dp[row - 1][col + 1][0] + 1;
          dp[row][col][1] = 1;
        } else {
          dp[row][col][0] =
              dp[row - 1][col][0] + dp[row][col + 1][0]
                  - dp[row - 1][col + 1][0];
          dp[row][col][1] = 0;
        }
      }
    }
    return static_cast<int>(dp[size - 1][0][0]);
  }
};

int main() {
  Solution s;
  std::cout << s.countSubstrings("aba");
  return 0;
}
