#include <string>
#include <iostream>

using namespace std;

class Solution {
 public:
  // 1 <= s.length <= 10^5
  static string removeDuplicates(string &s) {

    size_t size = s.size();
    size_t pw = 1;
    size_t p = 1;

    while (p != size) {
      if (pw != 0 && s[pw - 1] == s[p]) {
        --pw;
      } else  {
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
  string s("abbaca");
  std::cout << Solution::removeDuplicates(s) << "\n";
  return 0;
}