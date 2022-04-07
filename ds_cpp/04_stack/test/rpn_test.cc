#include "stack.h"
#include "rpn.h"

#include <sstream>
#include <exception>

#include <gtest/gtest.h>

TEST(RpnTest, TestReadNumber) {
  using namespace ds_cpp;
  using namespace ds_cpp::rpn;

  Stack<double> stk;

  const char *str1 = "123.5";
  const char *str2 = "1234";

  auto p = str1;
  ReadNumber(p, stk);
  EXPECT_EQ(stk.Pop(), 123.5);

  p = str2;
  ReadNumber(p, stk);
  EXPECT_EQ(stk.Pop(), 1234);

  const char *str3 = "12xzvc34";
  p = str3;
  ReadNumber(p, stk);
  EXPECT_EQ(stk.Pop(), 12);
  EXPECT_EQ(p, str3 + 2);
}

TEST(RpnTest, TestEvaluate) {
  using namespace ds_cpp;
  using namespace ds_cpp::rpn;

  const char *str1 = "((0+(1+23)/4*5*67-8+9))";
  const char *str2 = "(0!+1)*2^(3!+4)-(5!-67-(8+9))";
  const char *str3 = "0!+2!";
  const char *str4 = "0!+2xx!";

  char *Rpn = (char *) std::malloc(1);
  *Rpn='\0';
  EXPECT_EQ(Evaluate(str1, Rpn), 2011);
  EXPECT_EQ(Evaluate(str2, Rpn), 2012);
  EXPECT_EQ(Evaluate(str3, Rpn), 3);
  EXPECT_THROW(Evaluate(str4, Rpn), std::runtime_error);
}

TEST(RpnTest, TestRpn) {
  using namespace ds_cpp;
  using namespace ds_cpp::rpn;

  const char *str1 = "((0+(1+23)/4*5*67-8+9))";
  const char *str2 = "(0!+1)*2^(3!+4)-(5!-67-(8+9))";
  const char *str3 = "0!+2!";

  char *Rpn1 = (char *) std::malloc(1);
  *Rpn1 ='\0';
  char *Rpn2 = (char *) std::malloc(1);
  *Rpn2 ='\0';
  char *Rpn3 = (char *) std::malloc(1);
  *Rpn3 ='\0';

  Evaluate(str1, Rpn1);
  EXPECT_STREQ(Rpn1, "0 1 23 + 4 / 5 * 67 * + 8 - 9 + ");

  Evaluate(str2, Rpn2);
  EXPECT_STREQ(Rpn2, "0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - - ");

  Evaluate(str3, Rpn3);
  EXPECT_STREQ(Rpn3, "0 ! 2 ! + ");
}
