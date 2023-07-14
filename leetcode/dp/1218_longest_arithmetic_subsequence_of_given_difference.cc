#include <vector>
#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int Delta = 20000;
int mp[40000] = {}; // x -> key

class Solution {
 public:
  int longestSubsequence(vector<int> &arr, int difference) {
    vector<int> dp(arr.size(), 1);
    memset(mp, -1, sizeof(mp));
    mp[arr[0] + Delta] = 0;
    int ans = 1;
    for (int i = 1; i < arr.size(); ++i) {
      auto pre = arr[i] - difference;
      if (mp[pre + Delta] != -1) {
        dp[i] = dp[mp[pre + Delta]] + 1;
        ans = max(ans, dp[i]);
      }
      mp[arr[i] + Delta] = i;
    }
    return ans;
  }
};

int main() {
  Solution sol;
  vector<int> vec{1, 2, 3, 4};
  cout << sol.longestSubsequence(vec, 1) << "\n";
  return 0;
}