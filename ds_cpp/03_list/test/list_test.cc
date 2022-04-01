#include "list_node.h"
#include "list.h"

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

// ListNode 测试 遍历测试
TEST(AccessTest, TestTraverse) {
  using namespace ds_cpp;

  using LNP = ListNode<int>::LNP;

  LNP mid = new ListNode<int>(2);
  LNP first = mid->InsertAsPred(1);
  LNP last = mid->InsertAsSucc(3);

  EXPECT_EQ(mid->data(), 2);
}