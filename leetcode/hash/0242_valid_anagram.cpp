#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#define T(T) (T - 'a')

using namespace std;

/*
 * easy 哈希
 * 是否出现 与 出现次数权为元素 做集合交集
 *
 * unordered_map 用于 unicode 字符 char16_t
 * map 常见用法 :
 *   map.insert({'1', 12});
 *   map[c]++
 *   map.erase('1');
 *   map.erase(it);
 */
class Solution {
 public:
  static bool isAnagram(const string &s, const string &t) {
    // unordered_map<char16_t, int> hs;
    vector<int> hs(26);
    size_t size;
    if ((size = s.size()) != t.size()) {
      return false;
    }
    for (size_t i = 0; i != size; ++i) {
      ++hs[T(s[i])];
      --hs[T(t[i])];
    }
    for (size_t i = 0; i != 26; ++i) {
      if (hs[i] != 0) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  Solution solution;
  auto v = solution.isAnagram("anagram", "nagaram");
}