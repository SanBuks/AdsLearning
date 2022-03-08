#include "ordinary_element.h"

#include <memory>

#include "gtest/gtest.h"
#define GTEST_COUT std::cout << "[---INFO---] "

TEST(OrdinaryElementTest, OrdinaryElementTest) {
  using namespace ds_cpp::ordinary_element;

  int array1[]{};
  int array2[]{1};
  int array3[]{1, 2, 3, 4, 5, 6, 7};
  int array4[]{1, 2, 3, 4, 5, 6, 7, 9, 10, 11};
  int *p;

  EXPECT_EQ(OrdinaryElement(array1, sizeof(array1) / sizeof(int), &p), -1);
  EXPECT_EQ(OrdinaryElement(array2, sizeof(array2) / sizeof(int), &p), -1);
  EXPECT_EQ(OrdinaryElement(array3, sizeof(array3) / sizeof(int), &p), 0);
  EXPECT_EQ(*p, 2);
  EXPECT_EQ(OrdinaryElement(array4, sizeof(array4) / sizeof(int), &p), 0);
  EXPECT_EQ(*p, 2);
}