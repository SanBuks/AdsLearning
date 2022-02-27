#include <iostream>
#include <string>

using namespace std;

/**
 * easy
 */

inline bool IsBackspace(char t) {
  return t == '#';
}

size_t ProcessString(string &s) {
  size_t size = s.size();
  size_t p = 0;
  for (size_t i = 0; i != size; ++i) {
    if (!IsBackspace(s[i])) {
      s[p++] = s[i];
    } else {
      if (p) {
        --p;
      }
    }
  }
  return p;
}

class Solution {
 public:
  bool static backspaceCompare(string &s, string &t) {
    size_t s_p = ProcessString(s);
    size_t t_p = ProcessString(t);
    if (s_p != t_p) {
      return false;
    }
    for (size_t i = 0; i != s_p; ++i) {
      if (s[i] != t[i]) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  string s("ab#c");
  string t("abd#d#c");
  cout << Solution::backspaceCompare(s, t);
  return 0;
}