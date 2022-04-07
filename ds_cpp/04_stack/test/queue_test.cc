#include "queue.h"

#include <exception>

#include <gtest/gtest.h>

// 队列基本操作测试
TEST(QueueTest, TestQueue) {
  using namespace ds_cpp;

  Queue<int> q;

  q.Enqueue(1);
  q.Enqueue(2);
  q.Enqueue(3);
  q.Front() = 100;

  EXPECT_EQ(!q.Empty(), true);
  EXPECT_EQ(q.Dequeue(), 100);

  EXPECT_EQ(!q.Empty(), true);
  EXPECT_EQ(q.Dequeue(), 2);

  EXPECT_EQ(!q.Empty(), true);
  EXPECT_EQ(q.Dequeue(), 3);

  EXPECT_EQ(!q.Empty(), false);
}