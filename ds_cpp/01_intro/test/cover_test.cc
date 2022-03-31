#include "cover.h"

#include "gtest/gtest.h"
#define GTEST_COUT std::cout << "[---INFO---] "

TEST(TestCover, CoverTest) {
  using namespace ds_cpp::cover;

  Table table(4);
  table.Cover(Table::Pos(2, 3));
}