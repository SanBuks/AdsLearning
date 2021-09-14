#include <string>
#include <iostream>

using namespace std;

/**
 * [DP : MEDIUM]
 */
static bool dp[1000][1000] = { 0 };
class Solution {
 public:
  string longestPalindrome(string s) {
    /**
     * leetcode 中数组值初始化发生没有预想到的行为, 要手动初始化
     */
    for (auto & i : dp) {
      for (bool & j : i) {
        j =false;
      }
    }
    for (size_t i = 0; i != s.size(); ++i) {
      dp[i][i] = true;
    }
    for (size_t i = 0; i != s.size() - 1; ++i) {
      dp[i][i + 1] = true;
    }
    size_t size = s.size();
    for (size_t row_index = 1; row_index != size; ++row_index) {
      for (size_t row = row_index, col = 0; row != size ; ++row, ++col) {
        if (dp[row - 1][col + 1] && s[col] == s[row]) {
          dp[row][col] = true;
        }
      }
    }

    for (size_t row_index = size - 1; row_index < size; --row_index) {
      for (size_t row = row_index, col = 0; row != size ; ++row, ++col) {
        if (dp[row][col]) {
          return s.substr(col, row - col + 1);
        }
      }
    }
    return s.substr(0, 1);
  }
};

int main() {
  Solution solution;
  cout << solution.longestPalindrome("cbbd");
}
