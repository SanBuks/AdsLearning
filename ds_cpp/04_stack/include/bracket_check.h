#ifndef DS_CPP_BRACKET_CHECK_H
#define DS_CPP_BRACKET_CHECK_H

#include "stack.h"

namespace ds_cpp {

namespace bracket_check {

// 括号匹配 对 str [lo, hi] 区间做括号匹配检查
bool BracketCheckI(const char str[], size_t lo, size_t hi) {
  if (lo > hi) {
    return true;
  }

  Stack<char> st;
  for (auto i = lo; i <= hi; ++i) {
    switch (str[i]) {
      case '(':
      case '[':
      case '{': st.Push(str[i]);
        break;
      case ')': if (st.Empty() || st.Pop() != '(') return false;
        break;
      case ']': if (st.Empty() || st.Pop() != '[') return false;
        break;
      case '}': if (st.Empty() || st.Pop() != '{') return false;
        break;
      default :
        break;
    }
  }
  return st.Empty();
}

// 缩小范围为 括号部分
void Trim(const char str[], size_t &lo, size_t &hi, char lc, char rc) {
  while (lo <= hi && str[lo] != lc && str[lo] != rc) { ++lo; }
  while (lo <= hi && str[hi] != lc && str[hi] != rc) { --hi; }
}

// 找到局部匹配部分 [lo, mi]
size_t Divide(const char str[], size_t lo, size_t hi, char lc, char rc) {
  auto m = lo;
  size_t lc_num = 0;
  while (m <= hi) {
    if (str[m] == lc) {
      ++lc_num;
    } else if (str[m] == rc) {
      --lc_num;
    }
    if (!lc_num) {
      return m;
    }
    ++m;
  }
  return m;
}

// 迭代版括号匹配, 只能限定一种括号匹配, 无法处理多括号混合问题
bool BracketCheckR(const char str[], size_t lo, size_t hi, char lc, char rc) {
  if (lo > hi) {
    return true;
  }

  Trim(str, lo, hi, lc, rc);
  if (lo > hi){         // 没有括号部分
    return true;
  }
  if (str[lo] == rc) {  // 开头为右括号
    return false;
  }

  auto mi = Divide(str, lo, hi, lc, rc);
  return mi <= hi &&
         BracketCheckR(str, lo + 1, mi - 1, lc, rc) &&
         BracketCheckR(str, mi + 1, hi, lc, rc);
}

}  // namespace ds_cpp::bracket_check

}  // namespace ds_cpp

#endif