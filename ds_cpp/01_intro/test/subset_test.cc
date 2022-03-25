#include "subset.h"

#include <gtest/gtest.h>

#define GTEST_COUT std::cout << "[---INFO---] "

class TestSubSet: public ::testing::Test {
 protected:
  TestSubSet()
      : unique_array1{}, unique_array2{1}, unique_array3{1, 2, 3, 4, 5, 6} {}
  std::vector<int> unique_array1;
  std::vector<int> unique_array2;
  std::vector<int> unique_array3;
};


TEST_F(TestSubSet, UniqueSubsetTest) {
  using namespace ds_cpp::subset;
  auto it1 = UniqueSubset(unique_array1);
  auto it2 = UniqueSubset(unique_array2);
  auto it3 = UniqueSubset(unique_array3);
  EXPECT_EQ(it1.size(), 1);
  EXPECT_EQ(it2.size(), 2);
  EXPECT_EQ(it3.size(), 64);
}

TEST_F(TestSubSet, UniqueSubsetIterTest) {
  using namespace ds_cpp::subset;
  auto it1 = UniqueSubsetIter(unique_array1);
  auto it2 = UniqueSubsetIter(unique_array2);
  auto it3 = UniqueSubsetIter(unique_array3);
  EXPECT_EQ(it1.size(), 1);
  EXPECT_EQ(it2.size(), 2);
  EXPECT_EQ(it3.size(), 64);
}

TEST_F(TestSubSet, UniqueSubsetRecurTest) {
  using namespace ds_cpp::subset;
  auto it1 = UniqueSubsetRecur(unique_array1);
  auto it2 = UniqueSubsetRecur(unique_array2);
  auto it3 = UniqueSubsetRecur(unique_array3);
  EXPECT_EQ(it1.size(), 1);
  EXPECT_EQ(it2.size(), 2);
  EXPECT_EQ(it3.size(), 64);
}
