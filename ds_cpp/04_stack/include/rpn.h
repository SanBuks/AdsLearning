#ifndef DS_CPP_RPN_H
#define DS_CPP_RPN_H

#include <cmath>
#include <cstring>
#include "stack.h"

namespace ds_cpp {

namespace rpn {

constexpr int kNopt = 9;

struct rpn_error {
  static constexpr const char *kUnknownOperation
      = "[ds_cpp:rpn]: Char2Index() unknown operation";
  static constexpr const char *kUnknownUnaryOperation
      = "[ds_cpp:rpn]: Calc() unknown unary operation";
  static constexpr const char *kUnknownBinaryOperation
      = "[ds_cpp:rpn]: Calc() unknown binary operation";
  static constexpr const char *kNegativeFactory
      = "[ds_cpp:rpn]: Calc() factory can not be factory";
  static constexpr const char *kUnknownPriority
      = "[ds_cpp:rpn]: Evaluate() unknown priority";
};

enum class kOpt : long long {
  NON = -1, ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
};

// 横向是当前操作符 纵向是栈顶操作符
constexpr char kPriority[kNopt][kNopt] = {
//        +    -    *    /    ^    !    (    )   \0
/* + */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* - */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* * */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* / */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* ^ */  '>', '>', '>', '>', '<', '<', '<', '>', '>',  // 2^3^5 == 2^(3^5)
/* ! */  '>', '>', '>', '>', '>', '>', ' ', '>', '>',  // 3!! == (3!)!
/* ( */  '<', '<', '<', '<', '<', '<', '<', '=', ' ',
/* ) */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/* \0*/  '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

// 字符 转换成 优先级表中的 下标
kOpt Char2Index(char c) {
  switch (c) {
    case '+':  return kOpt::ADD;
    case '-':  return kOpt::SUB;
    case '*':  return kOpt::MUL;
    case '/':  return kOpt::DIV;
    case '^':  return kOpt::POW;
    case '!':  return kOpt::FAC;
    case '(':  return kOpt::L_P;
    case ')':  return kOpt::R_P;
    case '\0': return kOpt::EOE;
    default:   throw std::runtime_error(rpn_error::kUnknownOperation);
  }
}

inline char OrderBetween(char o1, char o2){
  return kPriority[static_cast<long long>(Char2Index(o1))]
                  [static_cast<long long>(Char2Index(o2))];
}

// 双目计算
double Calc(double n1, char c, double n2) {
  switch (c) {
    case '+': return n1 + n2;
    case '-': return n1 - n2;
    case '*': return n1 * n2;
    case '/': return n1 / n2;
    case '^': return pow(n1, n2);
    default:  throw std::runtime_error(rpn_error::kUnknownBinaryOperation);
  }
}

// 单目计算
double Calc(char c, double n) {
  switch (c) {
    case '!': {
      if (n < 0) {
        throw std::runtime_error(rpn_error::kNegativeFactory);
      }
      if (0 == n) {
        return 1;
      }
      n = std::floor(n);
      double sum = n;
      while (--n > 0) {
        sum *= n;
      }
      return sum;
    }
    default: throw std::runtime_error(rpn_error::kUnknownUnaryOperation);
  }
}

// 从字符串中读取数字
void ReadNumber(const char * &S, Stack<double> &stk) {
  stk.Push(*S - '0'); // 先放入数字
  while (std::isdigit(*(++S))) {
    stk.Top() *= 10;
    stk.Top() += *S - '0';
  }

  if ('.' != *S) {    // 如果没有小数部分则返回
    return;
  }
  double fraction = 1;
  while (std::isdigit(*(++S))) {
    stk.Top() += (*S - '0') * (fraction /= 10);
  }
}

void AppendChar(char *&rpn, char c) {
  auto n = std::strlen(rpn);
  rpn = (char *) realloc(rpn, n + 3);
  sprintf(rpn + n, "%c ", c);
  rpn[n + 2] = '\0';
}

void AppendNumber(char *&rpn, double num) {
  auto n = strlen(rpn);
  char buf[64];
  if (num != std::floor(num)) {
    sprintf(buf, "%.2f \0", num);
  } else {
    sprintf(buf, "%.0f \0", num);
  }
  rpn = (char *) realloc(rpn, n + strlen(buf) + 1);
  strcat(rpn, buf);
}

// 根据逆波兰表达式求 算术表达式
double Evaluate(const char *s, char * &rpn) {
  Stack<double> opn;
  Stack<char> opt;
  opt.Push('\0');

  while (!opt.Empty()) {
    if (std::isdigit(*s)) {
      ReadNumber(s, opn);
      AppendNumber(rpn, opn.Top());
    } else {
      switch (OrderBetween(opt.Top(), *s)) {
        case '<': {
          opt.Push(*s++);
          break;
        }
        case '=': {
          opt.Pop();
          s++;
          break;
        }
        case '>' : {
          auto op = opt.Pop();
          AppendChar(rpn, op);
          if ('!' == op) {
            auto number = opn.Pop();
            opn.Push(Calc(op, number));
          } else {
            auto number2 = opn.Pop();
            auto number1 = opn.Pop();
            opn.Push(Calc(number1, op, number2));
          }
          break;
        }
        default : {
          throw std::runtime_error(rpn_error::kUnknownPriority);
        }
      }
    }
  }
  return opn.Pop();
}

}  // namespace ds_cpp::rpn

}  // namespace ds_cpp

#endif