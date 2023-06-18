#include <vector>
#include <iostream>

using namespace std;


class Solution {
 public:

  int numOfWays(vector<int> &nums) {
    vector<vector<long long>> tri(nums.size() + 1);
    const int MOD = 1000'000'000 + 7;
    for (int row = 0; row < tri.size(); ++row) {
      tri[row] = vector<long long>(row + 1);
      for (int col = 0; col < row + 1; ++col) {
        if (col == 0) {
          tri[row][col] = 1;
        } else if (col == row) {
          tri[row][col] = 1;
        } else {
          tri[row][col] = (tri[row - 1][col] + tri[row - 1][col - 1]) % MOD;
        }
      }
    }
    return (Divide(nums, tri) - 1) % MOD;
  }

  long long Divide(vector<int> &nums, const vector<vector<long long>> &tri) {
    const int MOD = 1000'000'000 + 7;
    int root = nums[0];
    int size = static_cast<int>(nums.size());
    vector<int> left;
    vector<int> right;
    for (int i = 1; i < size; ++i) {
      if (nums[i] > root) {
        right.push_back(nums[i]);
      } else {
        left.push_back(nums[i]);
      }
    }
    long long com = tri[size - 1][static_cast<int>(left.size())];

    long long l_ans = left.size() > 1 ? Divide(left, tri) : 1;
    long long r_ans = right.size() > 1 ? Divide(right, tri) : 1;
    return (l_ans * r_ans) % MOD * com % MOD;
  }
};


int main() {
  Solution sol;
//  vector<int> nums{2, 1, 3};
  vector<int> nums{3, 4, 5, 1, 2};

  cout << sol.numOfWays(nums) << "\n";
  return 0;
}