#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#define T(T) (T - 'a')

using namespace std;

const int kSize = 26;
/*
 * easy 哈希
 * 是否出现 与 出现次数权为元素 做集合交集
 *
 */
class Solution {
 public:
  bool canConstruct(const string &ransomNote, const string &magazine) {
    int hs[kSize] = {};
    for (const auto &c : magazine) {
      ++hs[T(c)];
    }
    for (const auto &c : ransomNote) {
      if (--hs[T(c)] < 0) return false;
    }
    return true;
  }
};