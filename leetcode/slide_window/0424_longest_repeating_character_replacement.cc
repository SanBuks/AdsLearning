#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <map>

using namespace std;

class Solution {
 public:
  int characterReplacement(string s, int k) {
    int ans = 0;
    int low = 0;
    map<char, int> mp;
    for (int i = 0; i < 26; ++i) {
      mp[static_cast<char>('A' + i)] = 0;
    }

    for (int i = 0; i < s.size(); ++i) {
      ++mp[s[i]];

      while (foo(mp) > k) {
        --mp[s[low]];
        ++low;
      }
      ans = max(ans, i - low + 1);
    }
    return ans;
  }

  int foo(map<char, int> &mp) {
    int maxi = 0;
    int sum = 0;
    for (auto &item : mp) {
      maxi = max(maxi, item.second);
      sum += item.second;
    }
    return sum - maxi;
  }
};

int main() {

  Solution sol;
  cout << sol.characterReplacement("ABAB", 2) << "\n";
  cout << sol.characterReplacement("AABABBA", 1) << "\n";


  return 0;
}
