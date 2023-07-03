#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool buddyStrings(string s, string goal) {
    if (s.size() != goal.size()) { return false; }

    vector<int> pos;

    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != goal[i]) {
        pos.push_back(i);
      }
    }

    if (pos.size() == 2) {
      swap(s[pos[0]], s[pos[1]]);
      return s == goal;
    } else if (pos.empty()) {
      sort(s.begin(), s.end());
      for (int i = 1; i != s.size(); ++i) {
        if (s[i] == s[i - 1]) {
          return true;
        }
      }
      return false;
    } else {
      return false;
    }
  }
};

int main() {
  Solution sol;

  cout << sol.buddyStrings("aa", "aa") << "\n";
  cout << sol.buddyStrings("ab", "ba") << "\n";
  cout << sol.buddyStrings("ab", "ab") << "\n";

  return 0;
}