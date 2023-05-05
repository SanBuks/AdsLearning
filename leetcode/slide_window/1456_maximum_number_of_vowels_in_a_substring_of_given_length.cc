#include <string>
#include <iostream>

using namespace std;

class Solution {
 public:
  static int maxVowels(const string &s, int k) {
    int size = static_cast<int>(s.size());
    int max = 0;

    int first_max_index = size <= k ? size : k;
    for (int i = 0; i < first_max_index; ++i) {
      if (isVowel(s[i])) {
        ++max;
      }
    }
    if (size <= k) { return max; }

    int left = 0;
    int right = k;
    int vowel_size = max;

    while (right <= size) {
      if (isVowel(s[left])) {
        --vowel_size;
      }
      ++left;
      if (isVowel(s[right])) {
        ++vowel_size;
      }
      ++right;

      max = vowel_size > max ? vowel_size : max;
    }

    return max;
  }

  static bool isVowel(char c) {
    if (c == 'a' || c == 'A' ||
        c == 'e' || c == 'E' ||
        c == 'i' || c == 'I' ||
        c == 'o' || c == 'O' ||
        c == 'u' || c == 'U') {
      return true;
    }
    return false;
  }
};

int main() {
  auto k = 3;
  auto s = "abciiidef";
  std::cout << Solution::maxVowels(s, k) << "\n";
}