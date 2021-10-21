#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
// #include <unordered_map>

/*
 * mid 哈希
 * 是否出现 与 出现次数权为元素 做键值
 *
 * map 键值 遵从严格弱序
 * map<Word, vector<string>, WordCompare> hs;
 *
 * 优化方向 : 可以通过排序作为键值
 */
using namespace std;

inline size_t CharSeq(char c) {
  return c - 'a';
}

// 记录 出现次数 作为键值
struct Word {
  explicit Word() = default;
  explicit Word(const string &str) {
    for (auto c : str) {
      ++wd_[CharSeq(c)];
    }
  }

  unsigned short wd_[26] = {0};
};

struct WordCompare {
   bool operator() (const Word& lhs, const Word& rhs) const {
     for (size_t i = 0; i != 26; ++i) {
       if(lhs.wd_[i] < rhs.wd_[i]) {
         return true;
       } else if (lhs.wd_[i] > rhs.wd_[i]) {
         return false;
       }
     }
     return false;
   }
};


class Solution {
public:
    static vector<vector<string>> groupAnagrams(const vector<string>& strs) {
      map<Word, vector<string>, WordCompare> hs;
      for (const auto &str : strs) {
        Word w(str);
        hs[w].push_back(str);
      }
      vector<vector<string>> vec(hs.size());
      size_t i = 0;
      for (const auto &item : hs) {
        if (!item.second.empty()) {
          vec[i++] = item.second;
        }
      }
      return vec;
    }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<string> strs = {"eat","tea","tan","ate","nat","bat",
                         "eat","tea","tan","ate","nat","bat"};
  auto result = Solution::groupAnagrams(strs);
  for (const auto &item : result) {
    for (const auto &str : item) {
      cout << str << " ";
    }
    cout << "\n";
  }
  return 0;
}