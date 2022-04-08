#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>

using namespace std;

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

  static int evalRPN(vector<string> &tokens) {
    stack<long> opn;
    for (const auto &item : tokens) {
      if (item.size() == 1 && !isdigit(item[0])) {
        auto num2 = opn.top(); opn.pop();
        auto num1 = opn.top(); opn.pop();
        opn.push(Calc(num1, item[0], num2));
      } else {
        opn.push(strtol(item.c_str(), nullptr, 10));
      }
    }
    return static_cast<int>(opn.top());
  }
};
