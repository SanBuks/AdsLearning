#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

enum class kOpt : long long {
  NON = -1, ADD, SUB, MUL, DIV, LP, RP, UNA, EOE
};

const char kPriority[8][8] = {
//        +    -    *    /    (    )    u    \0
/* + */  '>', '>', '<', '<', '<', '>', '<', '>',
/* - */  '>', '>', '<', '<', '<', '>', '<', '>',
/* * */  '>', '>', '>', '>', '<', '>', '<', '>',
/* / */  '>', '>', '>', '>', '<', '>', '<', '>',
/* ( */  '<', '<', '<', '<', '<', '=', '<', '>',
/* ) */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/* u */  '>', '>', '>', '>', '<', '>', ' ', '>',
/*\0 */  '<', '<', '<', '<', '<', '<', '<', '='
};

kOpt Char2Index(char c) {
  switch (c) {
    case '+':  return kOpt::ADD;
    case '-':  return kOpt::SUB;
    case '*':  return kOpt::MUL;
    case '/':  return kOpt::DIV;
    case '(':  return kOpt::LP;
    case ')':  return kOpt::RP;
    case 'u':  return kOpt::UNA;
    case '\0': return kOpt::EOE;
    default: exit(EXIT_FAILURE);
  }
}

inline char OrderBetween(char o1, char o2) {
  return kPriority[static_cast<long long>(Char2Index(o1))]
                  [static_cast<long long>(Char2Index(o2))];
}

class Solution {
 public:
  static long Calc(long num1, char c, long num2) {
    switch (c) {
      case '+': return num1 + num2;
      case '-': return num1 - num2;
      case '*': return num1 * num2;
      case '/': return num1 / num2;
      default: exit(EXIT_FAILURE);
    }
  }

  static long Calc(long num1, char c) {
    switch (c) {
      case 'u': return -num1;
      default: exit(EXIT_FAILURE);
    }
  }

  static bool IsNumber(const string &s, size_t p) {
    return isdigit(s[p]) ||
           (s[p] == '-' && p + 1 != s.size() && isdigit(s[p + 1]) &&
            (p == 0 || s[p - 1] == '('));
  }

  static long ReadNumber(const string &s, size_t &p) {
    bool negative = (s[p] == '-');
    p += negative ? 1 : 0;
    long num = s[p++] - '0';
    while (p != s.size() && isdigit(s[p])) {
      num = num * 10 + s[p] - '0';
      ++p;
    }
    return negative ? -num : num;
  }

  static char ReadOpt(const string &s, size_t p) {
    auto size = s.size();

    // 判断是否是单目负号
    // -(3 + 2)
    // 1+(-(1 + 1))
    if (s[p] == '-' &&  p + 1 != size && s[p + 1] == '(' &&
        (p == 0 || s[p - 1] == '(')) {
      return 'u';
    } else {
      return s[p];
    }
  }

  static void Trim(string &s) {
    size_t pw = 0;
    size_t p = 0;
    size_t size = s.size();
    while (p != size) {
      if (!isspace(s[p])) {
        s[pw++] = s[p];
      }
      ++p;
    }
    s.resize(pw);
  }

  static int calculate(string &s) {
    stack<long> opn;
    stack<char> opt;

    Trim(s);

    s.push_back('\0');
    opt.push('\0');
    size_t size = s.size();
    size_t p = 0;

    while (!opt.empty()) {
      if (p >= size) {
        exit(EXIT_FAILURE);
      } else if (IsNumber(s, p)) {
        opn.push(ReadNumber(s, p));
      } else {
        auto op = ReadOpt(s, p);
        switch (OrderBetween(opt.top(), op)) {
          case '<': {
            opt.push(op);
            ++p;
            break;
          }
          case '=': {
            opt.pop();
            ++p;
            break;
          }
          case '>' : {
            op = opt.top();
            opt.pop();
            if ('u' == op) {
              auto num1 = opn.top();
              opn.pop();
              opn.push(Calc(num1, op));
            } else {
              auto num2 = opn.top(); opn.pop();
              auto num1 = opn.top(); opn.pop();
              opn.push(Calc(num1, op, num2));
            }
            break;
          }
          default: exit(EXIT_FAILURE);
        }
      }
    }
    return static_cast<int>(opn.top());
  }
};

int main() {
//  string s("(1+(4+5+2)-3)+(6+8)");
//  string s(" 2-1 + 2 ");
  string s("3 + (-(1 + 1))");
//  string s("-(2 + 3)");
  cout << Solution::calculate(s) << "\n";
  return EXIT_SUCCESS;
}
