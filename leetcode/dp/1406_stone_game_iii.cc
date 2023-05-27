#include <vector>
#include <string>
#include <cstring>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
 public:
  enum Player { Alice = 0, Bob };
  enum Type { Value = 0, Status };

  int size;
  int dp[2][50001][2];

  string stoneGameIII(vector<int> &stoneValue) {
    int sum = accumulate(stoneValue.begin(), stoneValue.end(), 0);
    size = static_cast<int> (stoneValue.size());
    memset(dp, -1, sizeof(dp));

    int alice_value = Dfs(stoneValue, Player::Alice, 0);
    cout << alice_value << "\n";
    if (sum - alice_value > alice_value) {
      return "Bob";
    } else if (sum - alice_value < alice_value) {
      return "Alice";
    } else {
      return "Tie";
    }
  }

  int Dfs(vector<int> &stoneValue, int p, int index) {
    if (index == size) { return 0; }

    int result = (p == 0 ? -50000001 : 50000001);
    int sum = 0;

    for (int i = 0; i < 3 && index + i < size; ++i) {
      if (p == Player::Alice) {
        if (dp[Player::Bob][index + i + 1][Type::Status] == -1) {
          dp[Player::Bob][index + i + 1][Type::Status] = 0;
          dp[Player::Bob][index + i + 1][Type::Value] = Dfs(stoneValue, Player::Bob, index + i + 1);
        }
        sum += stoneValue[index + i];
        result = max(result, sum + dp[Player::Bob][index + i + 1][Type::Value]);
      } else {
        if (dp[Player::Alice][index + i + 1][Type::Status] == -1) {
          dp[Player::Alice][index + i + 1][Type::Status] = 0;
          dp[Player::Alice][index + i + 1][Type::Value] = Dfs(stoneValue, Player::Alice, index + i + 1);
        }
        result = min(result, dp[Player::Alice][index + i + 1][Type::Value]);
      }
    }
    return result;
  }
};

int main() {
//  vector<int> stones{1, 2, 3, 7};
//  vector<int> stones{1, 2, 3, -9};
//  vector<int> stones{1, 2, 3, 6};
  vector<int> stones{-1, -2, -3};

  Solution sol{};
  cout << sol.stoneGameIII(stones) << "\n";

  return 0;
}