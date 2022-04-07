#include "stack.h"
#include "conversion.h"
#include "bracket_check.h"

#include <sstream>
#include <cstring>
#include <exception>

#include <gtest/gtest.h>

// 栈基本操作测试
TEST(StackTest, TestStack) {
  using namespace ds_cpp;

  Stack<int> s;
  s.Push(1);
  s.Push(2);
  s.Push(3);
  s.Top() = 100;

  EXPECT_EQ(!s.Empty(), true);
  EXPECT_EQ(s.Pop(), 100);

  EXPECT_EQ(!s.Empty(), true);
  EXPECT_EQ(s.Pop(), 2);

  EXPECT_EQ(!s.Empty(), true);
  EXPECT_EQ(s.Pop(), 1);

  EXPECT_EQ(!s.Empty(), false);
}

// 十进制 转换为 任意进制
TEST(StackTest, TestConversion) {
  using namespace ds_cpp;
  using namespace ds_cpp::conversion;

  std::ostringstream oss;

  oss.str("");
  Convert(oss, 2020, 16);
  EXPECT_EQ(oss.str(), "7E4");

  oss.str("");
  Convert(oss, 782369, 8);
  EXPECT_EQ(oss.str(), "2770041");

  oss.str("");
  Convert(oss, 23, 2);
  EXPECT_EQ(oss.str(), "10111");

  oss.str("");
  Convert(oss, -2, 2);
  EXPECT_EQ(oss.str(), "-10");
}

// 迭代括号检查
TEST(StackTest, TestBracketCheckI) {
  using namespace ds_cpp;
  using namespace ds_cpp::bracket_check;

  const char str1[] = "1[2]+((15+16))-{((12-19)+72)}-2";
  EXPECT_EQ(BracketCheckI(str1, 0, strlen(str1) - 1), true);

  const char str2[] = "12+((15+16))-((12)19)+72)-2";
  EXPECT_EQ(BracketCheckI(str2, 0, strlen(str2) - 1), false);
}

// 递归括号检查
TEST(StackTest, TestBracketCheckR) {
  using namespace ds_cpp;
  using namespace ds_cpp::bracket_check;

  const char str1[] = "12+((15+16))-((1219)+72)-2";
  EXPECT_EQ(BracketCheckR(str1, 0, strlen(str1) - 1, '(', ')'), true);

  const char str2[] = "12+((15+16))-((12)19)+72)-2";
  EXPECT_EQ(BracketCheckR(str2, 0, strlen(str2) - 1, '(', ')'), false);
}