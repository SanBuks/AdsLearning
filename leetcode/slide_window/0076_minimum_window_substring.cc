#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
 public:

  // 待优化: mp, count, compare to 0 取代 st, mp_d

  // m == s.length, n == t.length
  // 1 <= m, n <= 10^5
  // s and t consist of uppercase and lowercase English letters.
  string static minWindow(string &s, string &t) {
    unordered_map<char, int> mp;
    unordered_map<char, int> mp_d;
    std::unordered_set<char> st;
    size_t s_length = s.size();
    size_t t_length = t.size();
    for (size_t i = 0; i < t_length; ++i) {
      mp[t[i]] == 0 ? mp[t[i]] = 1 : ++mp[t[i]];
      st.insert(t[i]);
    }

    // 找到第一个数
    size_t begin = 0;
    while (begin < s_length && mp.find(s[begin]) == mp.end()) {
      ++begin;
    }
    if (begin < s_length) {
      --mp[s[begin]] == 0 ? mp.erase(s[begin]) : 0;
    }
    if (mp.empty()) {
      return {s.begin() + begin, s.begin() + begin + 1};
    }

    size_t max_length = SIZE_MAX;
    std::pair<size_t, size_t> range{begin, SIZE_MAX};
    for (size_t end = begin + 1;  end < s_length; ++end) {
      if (!mp.empty()) {
        if (mp.find(s[end]) != mp.end()) {
          --mp[s[end]] == 0 ? mp.erase(s[end]) : 0;
        } else if (st.find(s[end]) != st.end()) {
          mp_d[s[end]] == 0 ? mp_d[s[end]] = 1 : ++mp_d[s[end]];
        }
      }
      while (mp.empty()) {
        if (end - begin + 1 < max_length) {
          range.first = begin;
          range.second = end;
          max_length = range.second - range.first + 1;
        }
        if (st.find(s[begin]) != st.end()) {
          if (mp_d.find(s[begin]) != mp_d.end()) {
            --mp_d[s[begin]] == 0 ? mp_d.erase(s[begin]) : 0;
          } else {
            mp[s[begin]] == 0 ? mp[s[begin]] = 1 : ++mp[s[begin]];
          }
        }
        ++begin;
      }
    }
    return max_length != SIZE_MAX ?
           string(s.begin() + range.first, s.begin() + range.second + 1) : string();
  }
};

int main() {
//  string s("ADOBECODEBANC");
//  string t("ABC");
  string s("ab");
  string t("b");
  std::cout << Solution::minWindow(s, t);
  return 0;
}