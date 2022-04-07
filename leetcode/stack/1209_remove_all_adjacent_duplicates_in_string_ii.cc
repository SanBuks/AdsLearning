#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
 public:
  // 1 <= s.length <= 10^5
  static string removeDuplicates(string &s, int k) {

    auto size = s.size();
    size_t pw = 1;
    size_t p = 1;
    vector<int> len(size, 0);  // 记录以 0 为结尾的连串长度
    len[0] = 1;

    while (p != size) {
      if (pw != 0 && s[p] == s[pw - 1] && len[pw - 1] == (k - 1)) {
        pw -= k - 1;
      } else if (pw != 0 && s[p] == s[pw - 1]) {
        len[pw] = len[pw - 1] + 1;
        s[pw] = s[p];
        ++pw;
      } else {
        len[pw] = 1;
        s[pw] = s[p];
        ++pw;
      }
      ++p;
    }
    s.resize(pw);
    return s;
  }
};

int main() {
//  string s("abcd");
//  cout << Solution::removeDuplicates(s, 2) << "\n";

//  string s("deeedbbcccbdaa");
//  cout << Solution::removeDuplicates(s, 3) << "\n";

  string s("pbbcggttciiippooaais");
  cout << Solution::removeDuplicates(s, 2) << "\n";

  return 0;
}