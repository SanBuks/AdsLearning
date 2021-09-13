#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

/* [MATH : HARD]
 * 数学证明 k > 1 后可按任意顺序排列
 * [1 <=> 5]
 * [1, 2, 3, 4, 5] ->
 * [1, 5, 2, 3, 4] ->
 * [5, 2, 3, 4, 1]
 */
class Solution {
 public:
  string orderlyQueue(string s, int k) {
    if (k > 1) {
      std::sort(s.begin(), s.end());
      return s;
    } else {
      size_t num = s.size();
      std::string min(s);
      for (size_t i = 1; i != num; ++i) {
        char c = s[0];
        s.erase(0, 1);
        s.push_back(c);
        min = s < min ? s : min;
      }
      return min;
    }
  }
};

int main() {
  Solution s;
  std::cout << s.orderlyQueue("cba", 1);
  return 0;
}